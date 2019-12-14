/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <grpc/support/port_platform.h>

#include <limits.h>
#include <memory.h>

#include <grpc/fork.h>
#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/time.h>
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/channelz_registry.h"
#include "src/core/lib/channel/connected_channel.h"
#include "src/core/lib/channel/handshaker_registry.h"
#include "src/core/lib/debug/stats.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/gprpp/fork.h"
#include "src/core/lib/gprpp/sync.h"
#include "src/core/lib/http/parser.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/combiner.h"
#include "src/core/lib/iomgr/executor.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/lib/iomgr/resource_quota.h"
#include "src/core/lib/iomgr/timer_manager.h"
#include "src/core/lib/profiling/timers.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/surface/api_trace.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/surface/channel_init.h"
#include "src/core/lib/surface/completion_queue.h"
#include "src/core/lib/surface/init.h"
#include "src/core/lib/surface/lame_client.h"
#include "src/core/lib/surface/server.h"
#include "src/core/lib/transport/bdp_estimator.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/lib/transport/transport_impl.h"

/* (generated) built in registry of plugins */
extern void grpc_register_built_in_plugins(void);

#define MAX_PLUGINS 128

static gpr_once g_basic_init = GPR_ONCE_INIT;
static gpr_mu g_init_mu;
static int g_initializations;
static gpr_cv* g_shutting_down_cv;
static bool g_shutting_down;

static void do_basic_init(void) {
  gpr_log_verbosity_init();
  gpr_mu_init(&g_init_mu);
  g_shutting_down_cv = static_cast<gpr_cv*>(malloc(sizeof(gpr_cv)));
  gpr_cv_init(g_shutting_down_cv);
  g_shutting_down = false;
  grpc_register_built_in_plugins();
  grpc_cq_global_init();
  gpr_time_init();
  g_initializations = 0;
}

static bool append_filter(grpc_channel_stack_builder* builder, void* arg) {
  return grpc_channel_stack_builder_append_filter(
      builder, static_cast<const grpc_channel_filter*>(arg), nullptr, nullptr);
}

static bool prepend_filter(grpc_channel_stack_builder* builder, void* arg) {
  return grpc_channel_stack_builder_prepend_filter(
      builder, static_cast<const grpc_channel_filter*>(arg), nullptr, nullptr);
}

static void register_builtin_channel_init() {
  grpc_channel_init_register_stage(GRPC_CLIENT_SUBCHANNEL,
                                   GRPC_CHANNEL_INIT_BUILTIN_PRIORITY,
                                   grpc_add_connected_filter, nullptr);
  grpc_channel_init_register_stage(GRPC_CLIENT_DIRECT_CHANNEL,
                                   GRPC_CHANNEL_INIT_BUILTIN_PRIORITY,
                                   grpc_add_connected_filter, nullptr);
  grpc_channel_init_register_stage(GRPC_SERVER_CHANNEL,
                                   GRPC_CHANNEL_INIT_BUILTIN_PRIORITY,
                                   grpc_add_connected_filter, nullptr);
  grpc_channel_init_register_stage(GRPC_CLIENT_LAME_CHANNEL,
                                   GRPC_CHANNEL_INIT_BUILTIN_PRIORITY,
                                   append_filter, (void*)&grpc_lame_filter);
  grpc_channel_init_register_stage(GRPC_SERVER_CHANNEL, INT_MAX, prepend_filter,
                                   (void*)&grpc_server_top_filter);
}

typedef struct grpc_plugin {
  void (*init)();
  void (*destroy)();
} grpc_plugin;

static grpc_plugin g_all_of_the_plugins[MAX_PLUGINS];
static int g_number_of_plugins = 0;

void grpc_register_plugin(void (*init)(void), void (*destroy)(void)) {
  GRPC_API_TRACE("grpc_register_plugin(init=%p, destroy=%p)", 2,
                 ((void*)(intptr_t)init, (void*)(intptr_t)destroy));
  GPR_ASSERT(g_number_of_plugins != MAX_PLUGINS);
  g_all_of_the_plugins[g_number_of_plugins].init = init;
  g_all_of_the_plugins[g_number_of_plugins].destroy = destroy;
  g_number_of_plugins++;
}

void grpc_init(void) {
  int i;
  gpr_once_init(&g_basic_init, do_basic_init);

  grpc_core::MutexLock lock(&g_init_mu);
  if (++g_initializations == 1) {
    if (g_shutting_down) {
      g_shutting_down = false;
      gpr_cv_broadcast(g_shutting_down_cv);
    }
    grpc_core::Fork::GlobalInit();
    grpc_fork_handlers_auto_register();
    grpc_stats_init();
    grpc_init_static_metadata_ctx();
    grpc_slice_intern_init();
    grpc_mdctx_global_init();
    grpc_channel_init_init();
    grpc_core::channelz::ChannelzRegistry::Init();
    grpc_security_pre_init();
    grpc_core::ApplicationCallbackExecCtx::GlobalInit();
    grpc_core::ExecCtx::GlobalInit();
    grpc_iomgr_init();
    gpr_timers_global_init();
    grpc_core::HandshakerRegistry::Init();
    grpc_security_init();
    for (i = 0; i < g_number_of_plugins; i++) {
      if (g_all_of_the_plugins[i].init != nullptr) {
        g_all_of_the_plugins[i].init();
      }
    }
    /* register channel finalization AFTER all plugins, to ensure that it's run
     * at the appropriate time */
    grpc_register_security_filters();
    register_builtin_channel_init();
    grpc_tracer_init();
    /* no more changes to channel init pipelines */
    grpc_channel_init_finalize();
    grpc_iomgr_start();
  }

  GRPC_API_TRACE("grpc_init(void)", 0, ());
}

void grpc_shutdown_internal_locked(void) {
  int i;
  {
    grpc_core::ExecCtx exec_ctx(0);
    grpc_iomgr_shutdown_background_closure();
    {
      grpc_timer_manager_set_threading(false);  // shutdown timer_manager thread
      grpc_core::Executor::ShutdownAll();
      for (i = g_number_of_plugins; i >= 0; i--) {
        if (g_all_of_the_plugins[i].destroy != nullptr) {
          g_all_of_the_plugins[i].destroy();
        }
      }
    }
    grpc_iomgr_shutdown();
    gpr_timers_global_destroy();
    grpc_tracer_shutdown();
    grpc_mdctx_global_shutdown();
    grpc_core::HandshakerRegistry::Shutdown();
    grpc_slice_intern_shutdown();
    grpc_core::channelz::ChannelzRegistry::Shutdown();
    grpc_stats_shutdown();
    grpc_core::Fork::GlobalShutdown();
  }
  grpc_core::ExecCtx::GlobalShutdown();
  grpc_core::ApplicationCallbackExecCtx::GlobalShutdown();
  g_shutting_down = false;
  gpr_cv_broadcast(g_shutting_down_cv);
  // Absolute last action will be to delete static metadata context.
  grpc_destroy_static_metadata_ctx();
}

void grpc_shutdown_internal(void* ignored) {
  GRPC_API_TRACE("grpc_shutdown_internal", 0, ());
  grpc_core::MutexLock lock(&g_init_mu);
  // We have released lock from the shutdown thread and it is possible that
  // another grpc_init has been called, and do nothing if that is the case.
  if (--g_initializations != 0) {
    return;
  }
  grpc_shutdown_internal_locked();
}

void grpc_shutdown(void) {
  GRPC_API_TRACE("grpc_shutdown(void)", 0, ());
  grpc_core::MutexLock lock(&g_init_mu);
  if (--g_initializations == 0) {
    g_initializations++;
    g_shutting_down = true;
    // spawn a detached thread to do the actual clean up in case we are
    // currently in an executor thread.
    grpc_core::Thread cleanup_thread(
        "grpc_shutdown", grpc_shutdown_internal, nullptr, nullptr,
        grpc_core::Thread::Options().set_joinable(false).set_tracked(false));
    cleanup_thread.Start();
  }
}

void grpc_shutdown_blocking(void) {
  GRPC_API_TRACE("grpc_shutdown_blocking(void)", 0, ());
  grpc_core::MutexLock lock(&g_init_mu);
  if (--g_initializations == 0) {
    g_shutting_down = true;
    grpc_shutdown_internal_locked();
  }
}

int grpc_is_initialized(void) {
  int r;
  gpr_once_init(&g_basic_init, do_basic_init);
  grpc_core::MutexLock lock(&g_init_mu);
  r = g_initializations > 0;
  return r;
}

void grpc_maybe_wait_for_async_shutdown(void) {
  gpr_once_init(&g_basic_init, do_basic_init);
  grpc_core::MutexLock lock(&g_init_mu);
  while (g_shutting_down) {
    gpr_cv_wait(g_shutting_down_cv, &g_init_mu,
                gpr_inf_future(GPR_CLOCK_REALTIME));
  }
}

/************************************************
 * Workaround to support forking
 ***********************************************/
#include <set>
#include <vector>
#include <unistd.h>

static gpr_mu *grpc_mutex_socket_fd, *grpc_mutex_once, *grpc_mutex_mutex, *grpc_mutex_cond;
static std::vector<int> grpc_socket_fd;
static std::vector<pthread_once_t *> grpc_once;
static std::set<pthread_mutex_t *> grpc_mutex;
static std::set<pthread_cond_t *> grpc_cond;

static void my_mu_init(gpr_mu* mu) {
#ifdef GRPC_ASAN_ENABLED
    GPR_ASSERT(pthread_mutex_init(&mu->mutex, nullptr) == 0);
    mu->leak_checker = static_cast<int*>(malloc(sizeof(*mu->leak_checker)));
    GPR_ASSERT(mu->leak_checker != nullptr);
#else
    GPR_ASSERT(pthread_mutex_init(mu, nullptr) == 0);
#endif
}

/*
 * called from tcp_client_posix.cc when a socket is created
 */
void grpc_add_socket_fd(int fd) {
    grpc_core::MutexLock lock(grpc_mutex_socket_fd);
    grpc_socket_fd.push_back(fd);
}

/*
 * manually close sockets in forked process
 */
static void grpc_close_sockets() {
    for (auto fd : grpc_socket_fd) {
        close(fd);
    }
    grpc_socket_fd.clear();
}

/*
 * called from sync_posix.cc for every pthread_once()
 */
void grpc_add_once_init(pthread_once_t *once) {
    grpc_core::MutexLock lock(grpc_mutex_once);
    grpc_once.push_back(once);
}

/*
 * reset all pthread_once states in forked processes
 */
static void grpc_reset_once_inits() {
    for (auto o : grpc_once) {
        *o = 0;
    }
    grpc_once.clear();
}

/*
 * called from sync_posix.cc for every pthread_mutex_init()
 */
void grpc_add_mutex(pthread_mutex_t *mutex) {
    grpc_core::MutexLock lock(grpc_mutex_mutex);
    grpc_mutex.insert(mutex);
}

/*
 * called from sync_posix.cc for every pthread_mutex_destroy()
 */
void grpc_remove_mutex(pthread_mutex_t *mutex) {
    grpc_core::MutexLock lock(grpc_mutex_mutex);
    grpc_mutex.erase(mutex);
}

/*
 * reset all mutexes in forked processes
 */
static void grpc_reset_mutexes() {
    for (auto m : grpc_mutex) {
        memset(m, 0, sizeof(pthread_mutex_t));
    }
    grpc_mutex.clear();
}

/*
 * called from sync_posix.cc for every pthread_cond_init()
 */
void grpc_add_cond(pthread_cond_t *cond) {
    grpc_core::MutexLock lock(grpc_mutex_cond);
    grpc_cond.insert(cond);
}

/*
 * called from sync_posix.cc for every pthread_cond_destroy()
 */
void grpc_remove_cond(pthread_cond_t *cond) {
    grpc_core::MutexLock lock(grpc_mutex_cond);
    grpc_cond.erase(cond);
}

/*
 * reset all conds in forked processes
 */
static void grpc_reset_conds() {
    for (auto c : grpc_cond) {
        memset(c, 0, sizeof(pthread_cond_t));
    }
    grpc_cond.clear();
}

void grpc_clean_after_fork(void) {
    // init mutexes (use my_mu_init() instead of gpr_mu_init() so that we don't
    // add these to the list of GRPC mutexes)
    grpc_mutex_socket_fd = (gpr_mu *)malloc(sizeof(gpr_mu)); my_mu_init(grpc_mutex_socket_fd);
    grpc_mutex_once = (gpr_mu *)malloc(sizeof(gpr_mu)); my_mu_init(grpc_mutex_once);
    grpc_mutex_mutex = (gpr_mu *)malloc(sizeof(gpr_mu)); my_mu_init(grpc_mutex_mutex);
    grpc_mutex_cond = (gpr_mu *)malloc(sizeof(gpr_mu)); my_mu_init(grpc_mutex_cond);

    if (g_initializations == 0) {
        return;
    }

    /*
     * these variables hold a pointer to internal variables which
     * we manually need to reset before creating a new connection
     */
    extern void **fork_g_event_engine;                              // see ev_posix.cc
    extern void **fork_g_resolver_registry_state;                   // see resolver_registry.cc
    extern void **fork_g_policy_registry_state;                     // see lb_policy_registry.cc
    extern void **fork_g_handshaker_factory_lists;                  // see handshaker_registry.cc
    extern void **fork_g_registered_parsers;                        // see service_config.cc
    extern void **fork_g_current_source_addr_factory;               // see address_sorting.c
    extern void **fork_g_poller;                                    // see backup_poller.cc
    extern void **fork_g_grpc_control_plane_creds;                  // see credentials.cc
    extern void *fork_g_this_thread_state;                          // see executor.cc
    extern int fork_g_this_thread_state_size;                       // see executor.cc
    extern void *fork_executors;                                    // see executor.cc
    extern int fork_executors_size;                                 // see executor.cc
    extern void (*fork_reset_event_manager_on_fork)();              // see ev_epoll1_linux.cc

    grpc_close_sockets();
    grpc_reset_once_inits();
    grpc_reset_mutexes();
    grpc_reset_conds();

    // manually reset event manager
    (*fork_reset_event_manager_on_fork)();

    for (int i = 0; i < g_number_of_plugins; i++) {
        g_all_of_the_plugins[i].init = nullptr;
        g_all_of_the_plugins[i].destroy = nullptr;
    }
    g_number_of_plugins = 0;

    *fork_g_event_engine = nullptr;
    *fork_g_resolver_registry_state = nullptr;
    *fork_g_policy_registry_state = nullptr;
    *fork_g_handshaker_factory_lists = nullptr;
    *fork_g_registered_parsers = nullptr;
    *fork_g_current_source_addr_factory = NULL;
    *fork_g_poller = nullptr;
    *fork_g_grpc_control_plane_creds = nullptr;

    memset(fork_g_this_thread_state, 0, fork_g_this_thread_state_size);
    memset(fork_executors, 0, fork_executors_size);
}

//*************************************************

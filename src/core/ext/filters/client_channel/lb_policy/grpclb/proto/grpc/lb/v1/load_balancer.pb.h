/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.7-dev */

#ifndef PB_GRPC_LB_V1_LOAD_BALANCER_PB_H_INCLUDED
#define PB_GRPC_LB_V1_LOAD_BALANCER_PB_H_INCLUDED
#include "pb.h"
/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _grpc_lb_v1_ServerList {
    pb_callback_t servers;
/* @@protoc_insertion_point(struct:grpc_lb_v1_ServerList) */
} grpc_lb_v1_ServerList;

typedef struct _grpc_lb_v1_ClientStatsPerToken {
    pb_callback_t load_balance_token;
    bool has_num_calls;
    int64_t num_calls;
/* @@protoc_insertion_point(struct:grpc_lb_v1_ClientStatsPerToken) */
} grpc_lb_v1_ClientStatsPerToken;

typedef struct _grpc_lb_v1_Duration {
    bool has_seconds;
    int64_t seconds;
    bool has_nanos;
    int32_t nanos;
/* @@protoc_insertion_point(struct:grpc_lb_v1_Duration) */
} grpc_lb_v1_Duration;

typedef struct _grpc_lb_v1_InitialLoadBalanceRequest {
    bool has_name;
    char name[128];
/* @@protoc_insertion_point(struct:grpc_lb_v1_InitialLoadBalanceRequest) */
} grpc_lb_v1_InitialLoadBalanceRequest;

typedef PB_BYTES_ARRAY_T(16) grpc_lb_v1_Server_ip_address_t;
typedef struct _grpc_lb_v1_Server {
    bool has_ip_address;
    grpc_lb_v1_Server_ip_address_t ip_address;
    bool has_port;
    int32_t port;
    bool has_load_balance_token;
    char load_balance_token[50];
    bool has_drop;
    bool drop;
/* @@protoc_insertion_point(struct:grpc_lb_v1_Server) */
} grpc_lb_v1_Server;

typedef struct _grpc_lb_v1_Timestamp {
    bool has_seconds;
    int64_t seconds;
    bool has_nanos;
    int32_t nanos;
/* @@protoc_insertion_point(struct:grpc_lb_v1_Timestamp) */
} grpc_lb_v1_Timestamp;

typedef struct _grpc_lb_v1_ClientStats {
    bool has_timestamp;
    grpc_lb_v1_Timestamp timestamp;
    bool has_num_calls_started;
    int64_t num_calls_started;
    bool has_num_calls_finished;
    int64_t num_calls_finished;
    bool has_num_calls_finished_with_client_failed_to_send;
    int64_t num_calls_finished_with_client_failed_to_send;
    bool has_num_calls_finished_known_received;
    int64_t num_calls_finished_known_received;
    pb_callback_t calls_finished_with_drop;
/* @@protoc_insertion_point(struct:grpc_lb_v1_ClientStats) */
} grpc_lb_v1_ClientStats;

typedef struct _grpc_lb_v1_InitialLoadBalanceResponse {
    bool has_load_balancer_delegate;
    char load_balancer_delegate[64];
    bool has_client_stats_report_interval;
    grpc_lb_v1_Duration client_stats_report_interval;
/* @@protoc_insertion_point(struct:grpc_lb_v1_InitialLoadBalanceResponse) */
} grpc_lb_v1_InitialLoadBalanceResponse;

typedef struct _grpc_lb_v1_LoadBalanceRequest {
    bool has_initial_request;
    grpc_lb_v1_InitialLoadBalanceRequest initial_request;
    bool has_client_stats;
    grpc_lb_v1_ClientStats client_stats;
/* @@protoc_insertion_point(struct:grpc_lb_v1_LoadBalanceRequest) */
} grpc_lb_v1_LoadBalanceRequest;

typedef struct _grpc_lb_v1_LoadBalanceResponse {
    bool has_initial_response;
    grpc_lb_v1_InitialLoadBalanceResponse initial_response;
    bool has_server_list;
    grpc_lb_v1_ServerList server_list;
/* @@protoc_insertion_point(struct:grpc_lb_v1_LoadBalanceResponse) */
} grpc_lb_v1_LoadBalanceResponse;

/* Default values for struct fields */

/* Initializer values for message structs */
#define grpc_lb_v1_Duration_init_default         {false, 0, false, 0}
#define grpc_lb_v1_Timestamp_init_default        {false, 0, false, 0}
#define grpc_lb_v1_LoadBalanceRequest_init_default {false, grpc_lb_v1_InitialLoadBalanceRequest_init_default, false, grpc_lb_v1_ClientStats_init_default}
#define grpc_lb_v1_InitialLoadBalanceRequest_init_default {false, ""}
#define grpc_lb_v1_ClientStatsPerToken_init_default {{{NULL}, NULL}, false, 0}
#define grpc_lb_v1_ClientStats_init_default      {false, grpc_lb_v1_Timestamp_init_default, false, 0, false, 0, false, 0, false, 0, {{NULL}, NULL}}
#define grpc_lb_v1_LoadBalanceResponse_init_default {false, grpc_lb_v1_InitialLoadBalanceResponse_init_default, false, grpc_lb_v1_ServerList_init_default}
#define grpc_lb_v1_InitialLoadBalanceResponse_init_default {false, "", false, grpc_lb_v1_Duration_init_default}
#define grpc_lb_v1_ServerList_init_default       {{{NULL}, NULL}}
#define grpc_lb_v1_Server_init_default           {false, {0, {0}}, false, 0, false, "", false, 0}
#define grpc_lb_v1_Duration_init_zero            {false, 0, false, 0}
#define grpc_lb_v1_Timestamp_init_zero           {false, 0, false, 0}
#define grpc_lb_v1_LoadBalanceRequest_init_zero  {false, grpc_lb_v1_InitialLoadBalanceRequest_init_zero, false, grpc_lb_v1_ClientStats_init_zero}
#define grpc_lb_v1_InitialLoadBalanceRequest_init_zero {false, ""}
#define grpc_lb_v1_ClientStatsPerToken_init_zero {{{NULL}, NULL}, false, 0}
#define grpc_lb_v1_ClientStats_init_zero         {false, grpc_lb_v1_Timestamp_init_zero, false, 0, false, 0, false, 0, false, 0, {{NULL}, NULL}}
#define grpc_lb_v1_LoadBalanceResponse_init_zero {false, grpc_lb_v1_InitialLoadBalanceResponse_init_zero, false, grpc_lb_v1_ServerList_init_zero}
#define grpc_lb_v1_InitialLoadBalanceResponse_init_zero {false, "", false, grpc_lb_v1_Duration_init_zero}
#define grpc_lb_v1_ServerList_init_zero          {{{NULL}, NULL}}
#define grpc_lb_v1_Server_init_zero              {false, {0, {0}}, false, 0, false, "", false, 0}

/* Field tags (for use in manual encoding/decoding) */
#define grpc_lb_v1_ServerList_servers_tag        1
#define grpc_lb_v1_ClientStatsPerToken_load_balance_token_tag 1
#define grpc_lb_v1_ClientStatsPerToken_num_calls_tag 2
#define grpc_lb_v1_Duration_seconds_tag          1
#define grpc_lb_v1_Duration_nanos_tag            2
#define grpc_lb_v1_InitialLoadBalanceRequest_name_tag 1
#define grpc_lb_v1_Server_ip_address_tag         1
#define grpc_lb_v1_Server_port_tag               2
#define grpc_lb_v1_Server_load_balance_token_tag 3
#define grpc_lb_v1_Server_drop_tag               4
#define grpc_lb_v1_Timestamp_seconds_tag         1
#define grpc_lb_v1_Timestamp_nanos_tag           2
#define grpc_lb_v1_ClientStats_timestamp_tag     1
#define grpc_lb_v1_ClientStats_num_calls_started_tag 2
#define grpc_lb_v1_ClientStats_num_calls_finished_tag 3
#define grpc_lb_v1_ClientStats_num_calls_finished_with_client_failed_to_send_tag 6
#define grpc_lb_v1_ClientStats_num_calls_finished_known_received_tag 7
#define grpc_lb_v1_ClientStats_calls_finished_with_drop_tag 8
#define grpc_lb_v1_InitialLoadBalanceResponse_load_balancer_delegate_tag 1
#define grpc_lb_v1_InitialLoadBalanceResponse_client_stats_report_interval_tag 2
#define grpc_lb_v1_LoadBalanceRequest_initial_request_tag 1
#define grpc_lb_v1_LoadBalanceRequest_client_stats_tag 2
#define grpc_lb_v1_LoadBalanceResponse_initial_response_tag 1
#define grpc_lb_v1_LoadBalanceResponse_server_list_tag 2

/* Struct field encoding specification for nanopb */
extern const pb_field_t grpc_lb_v1_Duration_fields[3];
extern const pb_field_t grpc_lb_v1_Timestamp_fields[3];
extern const pb_field_t grpc_lb_v1_LoadBalanceRequest_fields[3];
extern const pb_field_t grpc_lb_v1_InitialLoadBalanceRequest_fields[2];
extern const pb_field_t grpc_lb_v1_ClientStatsPerToken_fields[3];
extern const pb_field_t grpc_lb_v1_ClientStats_fields[7];
extern const pb_field_t grpc_lb_v1_LoadBalanceResponse_fields[3];
extern const pb_field_t grpc_lb_v1_InitialLoadBalanceResponse_fields[3];
extern const pb_field_t grpc_lb_v1_ServerList_fields[2];
extern const pb_field_t grpc_lb_v1_Server_fields[5];

/* Maximum encoded size of messages (where known) */
#define grpc_lb_v1_Duration_size                 22
#define grpc_lb_v1_Timestamp_size                22
#define grpc_lb_v1_LoadBalanceRequest_size       (140 + grpc_lb_v1_ClientStats_size)
#define grpc_lb_v1_InitialLoadBalanceRequest_size 131
/* grpc_lb_v1_ClientStatsPerToken_size depends on runtime parameters */
/* grpc_lb_v1_ClientStats_size depends on runtime parameters */
#define grpc_lb_v1_LoadBalanceResponse_size      (98 + grpc_lb_v1_ServerList_size)
#define grpc_lb_v1_InitialLoadBalanceResponse_size 90
/* grpc_lb_v1_ServerList_size depends on runtime parameters */
#define grpc_lb_v1_Server_size                   83

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define LOAD_BALANCER_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif

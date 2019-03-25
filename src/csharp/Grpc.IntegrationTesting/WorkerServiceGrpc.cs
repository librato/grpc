// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: src/proto/grpc/testing/worker_service.proto
// </auto-generated>
// Original file comments:
// Copyright 2015 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// An integration test service that covers all the method signature permutations
// of unary/streaming requests/responses.
#pragma warning disable 0414, 1591
#region Designer generated code

using grpc = global::Grpc.Core;

namespace Grpc.Testing {
  public static partial class WorkerService
  {
    static readonly string __ServiceName = "grpc.testing.WorkerService";

    static readonly grpc::Marshaller<global::Grpc.Testing.ServerArgs> __Marshaller_grpc_testing_ServerArgs = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.ServerArgs.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Grpc.Testing.ServerStatus> __Marshaller_grpc_testing_ServerStatus = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.ServerStatus.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Grpc.Testing.ClientArgs> __Marshaller_grpc_testing_ClientArgs = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.ClientArgs.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Grpc.Testing.ClientStatus> __Marshaller_grpc_testing_ClientStatus = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.ClientStatus.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Grpc.Testing.CoreRequest> __Marshaller_grpc_testing_CoreRequest = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.CoreRequest.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Grpc.Testing.CoreResponse> __Marshaller_grpc_testing_CoreResponse = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.CoreResponse.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Grpc.Testing.Void> __Marshaller_grpc_testing_Void = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.Void.Parser.ParseFrom);

    static readonly grpc::Method<global::Grpc.Testing.ServerArgs, global::Grpc.Testing.ServerStatus> __Method_RunServer = new grpc::Method<global::Grpc.Testing.ServerArgs, global::Grpc.Testing.ServerStatus>(
        grpc::MethodType.DuplexStreaming,
        __ServiceName,
        "RunServer",
        __Marshaller_grpc_testing_ServerArgs,
        __Marshaller_grpc_testing_ServerStatus);

    static readonly grpc::Method<global::Grpc.Testing.ClientArgs, global::Grpc.Testing.ClientStatus> __Method_RunClient = new grpc::Method<global::Grpc.Testing.ClientArgs, global::Grpc.Testing.ClientStatus>(
        grpc::MethodType.DuplexStreaming,
        __ServiceName,
        "RunClient",
        __Marshaller_grpc_testing_ClientArgs,
        __Marshaller_grpc_testing_ClientStatus);

    static readonly grpc::Method<global::Grpc.Testing.CoreRequest, global::Grpc.Testing.CoreResponse> __Method_CoreCount = new grpc::Method<global::Grpc.Testing.CoreRequest, global::Grpc.Testing.CoreResponse>(
        grpc::MethodType.Unary,
        __ServiceName,
        "CoreCount",
        __Marshaller_grpc_testing_CoreRequest,
        __Marshaller_grpc_testing_CoreResponse);

    static readonly grpc::Method<global::Grpc.Testing.Void, global::Grpc.Testing.Void> __Method_QuitWorker = new grpc::Method<global::Grpc.Testing.Void, global::Grpc.Testing.Void>(
        grpc::MethodType.Unary,
        __ServiceName,
        "QuitWorker",
        __Marshaller_grpc_testing_Void,
        __Marshaller_grpc_testing_Void);

    /// <summary>Service descriptor</summary>
    public static global::Google.Protobuf.Reflection.ServiceDescriptor Descriptor
    {
      get { return global::Grpc.Testing.WorkerServiceReflection.Descriptor.Services[0]; }
    }

    /// <summary>Base class for server-side implementations of WorkerService</summary>
    [grpc::BindService(typeof(WorkerService), "BindService")]
    public abstract partial class WorkerServiceBase
    {
      /// <summary>
      /// Start server with specified workload.
      /// First request sent specifies the ServerConfig followed by ServerStatus
      /// response. After that, a "Mark" can be sent anytime to request the latest
      /// stats. Closing the stream will initiate shutdown of the test server
      /// and once the shutdown has finished, the OK status is sent to terminate
      /// this RPC.
      /// </summary>
      /// <param name="requestStream">Used for reading requests from the client.</param>
      /// <param name="responseStream">Used for sending responses back to the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>A task indicating completion of the handler.</returns>
      public virtual global::System.Threading.Tasks.Task RunServer(grpc::IAsyncStreamReader<global::Grpc.Testing.ServerArgs> requestStream, grpc::IServerStreamWriter<global::Grpc.Testing.ServerStatus> responseStream, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

      /// <summary>
      /// Start client with specified workload.
      /// First request sent specifies the ClientConfig followed by ClientStatus
      /// response. After that, a "Mark" can be sent anytime to request the latest
      /// stats. Closing the stream will initiate shutdown of the test client
      /// and once the shutdown has finished, the OK status is sent to terminate
      /// this RPC.
      /// </summary>
      /// <param name="requestStream">Used for reading requests from the client.</param>
      /// <param name="responseStream">Used for sending responses back to the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>A task indicating completion of the handler.</returns>
      public virtual global::System.Threading.Tasks.Task RunClient(grpc::IAsyncStreamReader<global::Grpc.Testing.ClientArgs> requestStream, grpc::IServerStreamWriter<global::Grpc.Testing.ClientStatus> responseStream, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

      /// <summary>
      /// Just return the core count - unary call
      /// </summary>
      /// <param name="request">The request received from the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>The response to send back to the client (wrapped by a task).</returns>
      public virtual global::System.Threading.Tasks.Task<global::Grpc.Testing.CoreResponse> CoreCount(global::Grpc.Testing.CoreRequest request, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

      /// <summary>
      /// Quit this worker
      /// </summary>
      /// <param name="request">The request received from the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>The response to send back to the client (wrapped by a task).</returns>
      public virtual global::System.Threading.Tasks.Task<global::Grpc.Testing.Void> QuitWorker(global::Grpc.Testing.Void request, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

    }

    /// <summary>Client for WorkerService</summary>
    public partial class WorkerServiceClient : grpc::ClientBase<WorkerServiceClient>
    {
      /// <summary>Creates a new client for WorkerService</summary>
      /// <param name="channel">The channel to use to make remote calls.</param>
      public WorkerServiceClient(grpc::Channel channel) : base(channel)
      {
      }
      /// <summary>Creates a new client for WorkerService that uses a custom <c>CallInvoker</c>.</summary>
      /// <param name="callInvoker">The callInvoker to use to make remote calls.</param>
      public WorkerServiceClient(grpc::CallInvoker callInvoker) : base(callInvoker)
      {
      }
      /// <summary>Protected parameterless constructor to allow creation of test doubles.</summary>
      protected WorkerServiceClient() : base()
      {
      }
      /// <summary>Protected constructor to allow creation of configured clients.</summary>
      /// <param name="configuration">The client configuration.</param>
      protected WorkerServiceClient(ClientBaseConfiguration configuration) : base(configuration)
      {
      }

      /// <summary>
      /// Start server with specified workload.
      /// First request sent specifies the ServerConfig followed by ServerStatus
      /// response. After that, a "Mark" can be sent anytime to request the latest
      /// stats. Closing the stream will initiate shutdown of the test server
      /// and once the shutdown has finished, the OK status is sent to terminate
      /// this RPC.
      /// </summary>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncDuplexStreamingCall<global::Grpc.Testing.ServerArgs, global::Grpc.Testing.ServerStatus> RunServer(grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return RunServer(new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Start server with specified workload.
      /// First request sent specifies the ServerConfig followed by ServerStatus
      /// response. After that, a "Mark" can be sent anytime to request the latest
      /// stats. Closing the stream will initiate shutdown of the test server
      /// and once the shutdown has finished, the OK status is sent to terminate
      /// this RPC.
      /// </summary>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncDuplexStreamingCall<global::Grpc.Testing.ServerArgs, global::Grpc.Testing.ServerStatus> RunServer(grpc::CallOptions options)
      {
        return CallInvoker.AsyncDuplexStreamingCall(__Method_RunServer, null, options);
      }
      /// <summary>
      /// Start client with specified workload.
      /// First request sent specifies the ClientConfig followed by ClientStatus
      /// response. After that, a "Mark" can be sent anytime to request the latest
      /// stats. Closing the stream will initiate shutdown of the test client
      /// and once the shutdown has finished, the OK status is sent to terminate
      /// this RPC.
      /// </summary>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncDuplexStreamingCall<global::Grpc.Testing.ClientArgs, global::Grpc.Testing.ClientStatus> RunClient(grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return RunClient(new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Start client with specified workload.
      /// First request sent specifies the ClientConfig followed by ClientStatus
      /// response. After that, a "Mark" can be sent anytime to request the latest
      /// stats. Closing the stream will initiate shutdown of the test client
      /// and once the shutdown has finished, the OK status is sent to terminate
      /// this RPC.
      /// </summary>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncDuplexStreamingCall<global::Grpc.Testing.ClientArgs, global::Grpc.Testing.ClientStatus> RunClient(grpc::CallOptions options)
      {
        return CallInvoker.AsyncDuplexStreamingCall(__Method_RunClient, null, options);
      }
      /// <summary>
      /// Just return the core count - unary call
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The response received from the server.</returns>
      public virtual global::Grpc.Testing.CoreResponse CoreCount(global::Grpc.Testing.CoreRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return CoreCount(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Just return the core count - unary call
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The response received from the server.</returns>
      public virtual global::Grpc.Testing.CoreResponse CoreCount(global::Grpc.Testing.CoreRequest request, grpc::CallOptions options)
      {
        return CallInvoker.BlockingUnaryCall(__Method_CoreCount, null, options, request);
      }
      /// <summary>
      /// Just return the core count - unary call
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncUnaryCall<global::Grpc.Testing.CoreResponse> CoreCountAsync(global::Grpc.Testing.CoreRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return CoreCountAsync(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Just return the core count - unary call
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncUnaryCall<global::Grpc.Testing.CoreResponse> CoreCountAsync(global::Grpc.Testing.CoreRequest request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncUnaryCall(__Method_CoreCount, null, options, request);
      }
      /// <summary>
      /// Quit this worker
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The response received from the server.</returns>
      public virtual global::Grpc.Testing.Void QuitWorker(global::Grpc.Testing.Void request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return QuitWorker(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Quit this worker
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The response received from the server.</returns>
      public virtual global::Grpc.Testing.Void QuitWorker(global::Grpc.Testing.Void request, grpc::CallOptions options)
      {
        return CallInvoker.BlockingUnaryCall(__Method_QuitWorker, null, options, request);
      }
      /// <summary>
      /// Quit this worker
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncUnaryCall<global::Grpc.Testing.Void> QuitWorkerAsync(global::Grpc.Testing.Void request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return QuitWorkerAsync(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Quit this worker
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncUnaryCall<global::Grpc.Testing.Void> QuitWorkerAsync(global::Grpc.Testing.Void request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncUnaryCall(__Method_QuitWorker, null, options, request);
      }
      /// <summary>Creates a new instance of client from given <c>ClientBaseConfiguration</c>.</summary>
      protected override WorkerServiceClient NewInstance(ClientBaseConfiguration configuration)
      {
        return new WorkerServiceClient(configuration);
      }
    }

    /// <summary>Creates service definition that can be registered with a server</summary>
    /// <param name="serviceImpl">An object implementing the server-side handling logic.</param>
    public static grpc::ServerServiceDefinition BindService(WorkerServiceBase serviceImpl)
    {
      return grpc::ServerServiceDefinition.CreateBuilder()
          .AddMethod(__Method_RunServer, serviceImpl.RunServer)
          .AddMethod(__Method_RunClient, serviceImpl.RunClient)
          .AddMethod(__Method_CoreCount, serviceImpl.CoreCount)
          .AddMethod(__Method_QuitWorker, serviceImpl.QuitWorker).Build();
    }

    /// <summary>Register service method with a service binder with or without implementation. Useful when customizing the  service binding logic.
    /// Note: this method is part of an experimental API that can change or be removed without any prior notice.</summary>
    /// <param name="serviceBinder">Service methods will be bound by calling <c>AddMethod</c> on this object.</param>
    /// <param name="serviceImpl">An object implementing the server-side handling logic.</param>
    public static void BindService(grpc::ServiceBinderBase serviceBinder, WorkerServiceBase serviceImpl)
    {
      serviceBinder.AddMethod(__Method_RunServer, serviceImpl == null ? null : new grpc::DuplexStreamingServerMethod<global::Grpc.Testing.ServerArgs, global::Grpc.Testing.ServerStatus>(serviceImpl.RunServer));
      serviceBinder.AddMethod(__Method_RunClient, serviceImpl == null ? null : new grpc::DuplexStreamingServerMethod<global::Grpc.Testing.ClientArgs, global::Grpc.Testing.ClientStatus>(serviceImpl.RunClient));
      serviceBinder.AddMethod(__Method_CoreCount, serviceImpl == null ? null : new grpc::UnaryServerMethod<global::Grpc.Testing.CoreRequest, global::Grpc.Testing.CoreResponse>(serviceImpl.CoreCount));
      serviceBinder.AddMethod(__Method_QuitWorker, serviceImpl == null ? null : new grpc::UnaryServerMethod<global::Grpc.Testing.Void, global::Grpc.Testing.Void>(serviceImpl.QuitWorker));
    }

  }
}
#endregion

// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: src/proto/grpc/testing/metrics.proto
// </auto-generated>
// Original file comments:
// Copyright 2015-2016 gRPC authors.
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
// Contains the definitions for a metrics service and the type of metrics
// exposed by the service.
// 
// Currently, 'Gauge' (i.e a metric that represents the measured value of
// something at an instant of time) is the only metric type supported by the
// service.
#pragma warning disable 0414, 1591
#region Designer generated code

using grpc = global::Grpc.Core;

namespace Grpc.Testing {
  public static partial class MetricsService
  {
    static readonly string __ServiceName = "grpc.testing.MetricsService";

    static readonly grpc::Marshaller<global::Grpc.Testing.EmptyMessage> __Marshaller_grpc_testing_EmptyMessage = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.EmptyMessage.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Grpc.Testing.GaugeResponse> __Marshaller_grpc_testing_GaugeResponse = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.GaugeResponse.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Grpc.Testing.GaugeRequest> __Marshaller_grpc_testing_GaugeRequest = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Grpc.Testing.GaugeRequest.Parser.ParseFrom);

    static readonly grpc::Method<global::Grpc.Testing.EmptyMessage, global::Grpc.Testing.GaugeResponse> __Method_GetAllGauges = new grpc::Method<global::Grpc.Testing.EmptyMessage, global::Grpc.Testing.GaugeResponse>(
        grpc::MethodType.ServerStreaming,
        __ServiceName,
        "GetAllGauges",
        __Marshaller_grpc_testing_EmptyMessage,
        __Marshaller_grpc_testing_GaugeResponse);

    static readonly grpc::Method<global::Grpc.Testing.GaugeRequest, global::Grpc.Testing.GaugeResponse> __Method_GetGauge = new grpc::Method<global::Grpc.Testing.GaugeRequest, global::Grpc.Testing.GaugeResponse>(
        grpc::MethodType.Unary,
        __ServiceName,
        "GetGauge",
        __Marshaller_grpc_testing_GaugeRequest,
        __Marshaller_grpc_testing_GaugeResponse);

    /// <summary>Service descriptor</summary>
    public static global::Google.Protobuf.Reflection.ServiceDescriptor Descriptor
    {
      get { return global::Grpc.Testing.MetricsReflection.Descriptor.Services[0]; }
    }

    /// <summary>Base class for server-side implementations of MetricsService</summary>
    public abstract partial class MetricsServiceBase
    {
      /// <summary>
      /// Returns the values of all the gauges that are currently being maintained by
      /// the service
      /// </summary>
      /// <param name="request">The request received from the client.</param>
      /// <param name="responseStream">Used for sending responses back to the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>A task indicating completion of the handler.</returns>
      public virtual global::System.Threading.Tasks.Task GetAllGauges(global::Grpc.Testing.EmptyMessage request, grpc::IServerStreamWriter<global::Grpc.Testing.GaugeResponse> responseStream, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

      /// <summary>
      /// Returns the value of one gauge
      /// </summary>
      /// <param name="request">The request received from the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>The response to send back to the client (wrapped by a task).</returns>
      public virtual global::System.Threading.Tasks.Task<global::Grpc.Testing.GaugeResponse> GetGauge(global::Grpc.Testing.GaugeRequest request, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

    }

    /// <summary>Client for MetricsService</summary>
    public partial class MetricsServiceClient : grpc::ClientBase<MetricsServiceClient>
    {
      /// <summary>Creates a new client for MetricsService</summary>
      /// <param name="channel">The channel to use to make remote calls.</param>
      public MetricsServiceClient(grpc::Channel channel) : base(channel)
      {
      }
      /// <summary>Creates a new client for MetricsService that uses a custom <c>CallInvoker</c>.</summary>
      /// <param name="callInvoker">The callInvoker to use to make remote calls.</param>
      public MetricsServiceClient(grpc::CallInvoker callInvoker) : base(callInvoker)
      {
      }
      /// <summary>Protected parameterless constructor to allow creation of test doubles.</summary>
      protected MetricsServiceClient() : base()
      {
      }
      /// <summary>Protected constructor to allow creation of configured clients.</summary>
      /// <param name="configuration">The client configuration.</param>
      protected MetricsServiceClient(ClientBaseConfiguration configuration) : base(configuration)
      {
      }

      /// <summary>
      /// Returns the values of all the gauges that are currently being maintained by
      /// the service
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncServerStreamingCall<global::Grpc.Testing.GaugeResponse> GetAllGauges(global::Grpc.Testing.EmptyMessage request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return GetAllGauges(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Returns the values of all the gauges that are currently being maintained by
      /// the service
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncServerStreamingCall<global::Grpc.Testing.GaugeResponse> GetAllGauges(global::Grpc.Testing.EmptyMessage request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncServerStreamingCall(__Method_GetAllGauges, null, options, request);
      }
      /// <summary>
      /// Returns the value of one gauge
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The response received from the server.</returns>
      public virtual global::Grpc.Testing.GaugeResponse GetGauge(global::Grpc.Testing.GaugeRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return GetGauge(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Returns the value of one gauge
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The response received from the server.</returns>
      public virtual global::Grpc.Testing.GaugeResponse GetGauge(global::Grpc.Testing.GaugeRequest request, grpc::CallOptions options)
      {
        return CallInvoker.BlockingUnaryCall(__Method_GetGauge, null, options, request);
      }
      /// <summary>
      /// Returns the value of one gauge
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncUnaryCall<global::Grpc.Testing.GaugeResponse> GetGaugeAsync(global::Grpc.Testing.GaugeRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return GetGaugeAsync(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Returns the value of one gauge
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncUnaryCall<global::Grpc.Testing.GaugeResponse> GetGaugeAsync(global::Grpc.Testing.GaugeRequest request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncUnaryCall(__Method_GetGauge, null, options, request);
      }
      /// <summary>Creates a new instance of client from given <c>ClientBaseConfiguration</c>.</summary>
      protected override MetricsServiceClient NewInstance(ClientBaseConfiguration configuration)
      {
        return new MetricsServiceClient(configuration);
      }
    }

    /// <summary>Creates service definition that can be registered with a server</summary>
    /// <param name="serviceImpl">An object implementing the server-side handling logic.</param>
    public static grpc::ServerServiceDefinition BindService(MetricsServiceBase serviceImpl)
    {
      return grpc::ServerServiceDefinition.CreateBuilder()
          .AddMethod(__Method_GetAllGauges, serviceImpl.GetAllGauges)
          .AddMethod(__Method_GetGauge, serviceImpl.GetGauge).Build();
    }

    /// <summary>Register service method implementations with a service binder. Useful when customizing the service binding logic.
    /// Note: this method is part of an experimental API that can change or be removed without any prior notice.</summary>
    /// <param name="serviceBinder">Service methods will be bound by calling <c>AddMethod</c> on this object.</param>
    /// <param name="serviceImpl">An object implementing the server-side handling logic.</param>
    public static void BindService(grpc::ServiceBinderBase serviceBinder, MetricsServiceBase serviceImpl)
    {
      serviceBinder.AddMethod(__Method_GetAllGauges, serviceImpl.GetAllGauges);
      serviceBinder.AddMethod(__Method_GetGauge, serviceImpl.GetGauge);
    }

    /// <summary>Register service method with a service binder without implementation. Useful when customizing the service binding logic.
    /// Note: this method is part of an experimental API that can change or be removed without any prior notice.</summary>
    /// <param name="serviceBinder">Service methods will be bound by calling <c>AddMethod</c> on this object.</param>
    public static void BindService(grpc::ServiceBinderBase serviceBinder)
    {
      serviceBinder.AddMethod(__Method_GetAllGauges);
      serviceBinder.AddMethod(__Method_GetGauge);
    }

  }
}
#endregion

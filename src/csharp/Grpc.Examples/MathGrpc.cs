// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: math/math.proto
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
#pragma warning disable 0414, 1591
#region Designer generated code

using grpc = global::Grpc.Core;

namespace Math {
  public static partial class Math
  {
    static readonly string __ServiceName = "math.Math";

    static readonly grpc::Marshaller<global::Math.DivArgs> __Marshaller_math_DivArgs = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Math.DivArgs.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Math.DivReply> __Marshaller_math_DivReply = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Math.DivReply.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Math.FibArgs> __Marshaller_math_FibArgs = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Math.FibArgs.Parser.ParseFrom);
    static readonly grpc::Marshaller<global::Math.Num> __Marshaller_math_Num = grpc::Marshallers.Create((arg) => global::Google.Protobuf.MessageExtensions.ToByteArray(arg), global::Math.Num.Parser.ParseFrom);

    static readonly grpc::Method<global::Math.DivArgs, global::Math.DivReply> __Method_Div = new grpc::Method<global::Math.DivArgs, global::Math.DivReply>(
        grpc::MethodType.Unary,
        __ServiceName,
        "Div",
        __Marshaller_math_DivArgs,
        __Marshaller_math_DivReply);

    static readonly grpc::Method<global::Math.DivArgs, global::Math.DivReply> __Method_DivMany = new grpc::Method<global::Math.DivArgs, global::Math.DivReply>(
        grpc::MethodType.DuplexStreaming,
        __ServiceName,
        "DivMany",
        __Marshaller_math_DivArgs,
        __Marshaller_math_DivReply);

    static readonly grpc::Method<global::Math.FibArgs, global::Math.Num> __Method_Fib = new grpc::Method<global::Math.FibArgs, global::Math.Num>(
        grpc::MethodType.ServerStreaming,
        __ServiceName,
        "Fib",
        __Marshaller_math_FibArgs,
        __Marshaller_math_Num);

    static readonly grpc::Method<global::Math.Num, global::Math.Num> __Method_Sum = new grpc::Method<global::Math.Num, global::Math.Num>(
        grpc::MethodType.ClientStreaming,
        __ServiceName,
        "Sum",
        __Marshaller_math_Num,
        __Marshaller_math_Num);

    /// <summary>Service descriptor</summary>
    public static global::Google.Protobuf.Reflection.ServiceDescriptor Descriptor
    {
      get { return global::Math.MathReflection.Descriptor.Services[0]; }
    }

    /// <summary>Base class for server-side implementations of Math</summary>
    public abstract partial class MathBase
    {
      /// <summary>
      /// Div divides DivArgs.dividend by DivArgs.divisor and returns the quotient
      /// and remainder.
      /// </summary>
      /// <param name="request">The request received from the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>The response to send back to the client (wrapped by a task).</returns>
      public virtual global::System.Threading.Tasks.Task<global::Math.DivReply> Div(global::Math.DivArgs request, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

      /// <summary>
      /// DivMany accepts an arbitrary number of division args from the client stream
      /// and sends back the results in the reply stream.  The stream continues until
      /// the client closes its end; the server does the same after sending all the
      /// replies.  The stream ends immediately if either end aborts.
      /// </summary>
      /// <param name="requestStream">Used for reading requests from the client.</param>
      /// <param name="responseStream">Used for sending responses back to the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>A task indicating completion of the handler.</returns>
      public virtual global::System.Threading.Tasks.Task DivMany(grpc::IAsyncStreamReader<global::Math.DivArgs> requestStream, grpc::IServerStreamWriter<global::Math.DivReply> responseStream, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

      /// <summary>
      /// Fib generates numbers in the Fibonacci sequence.  If FibArgs.limit > 0, Fib
      /// generates up to limit numbers; otherwise it continues until the call is
      /// canceled.  Unlike Fib above, Fib has no final FibReply.
      /// </summary>
      /// <param name="request">The request received from the client.</param>
      /// <param name="responseStream">Used for sending responses back to the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>A task indicating completion of the handler.</returns>
      public virtual global::System.Threading.Tasks.Task Fib(global::Math.FibArgs request, grpc::IServerStreamWriter<global::Math.Num> responseStream, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

      /// <summary>
      /// Sum sums a stream of numbers, returning the final result once the stream
      /// is closed.
      /// </summary>
      /// <param name="requestStream">Used for reading requests from the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>The response to send back to the client (wrapped by a task).</returns>
      public virtual global::System.Threading.Tasks.Task<global::Math.Num> Sum(grpc::IAsyncStreamReader<global::Math.Num> requestStream, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

    }

    /// <summary>Client for Math</summary>
    public partial class MathClient : grpc::ClientBase<MathClient>
    {
      /// <summary>Creates a new client for Math</summary>
      /// <param name="channel">The channel to use to make remote calls.</param>
      public MathClient(grpc::Channel channel) : base(channel)
      {
      }
      /// <summary>Creates a new client for Math that uses a custom <c>CallInvoker</c>.</summary>
      /// <param name="callInvoker">The callInvoker to use to make remote calls.</param>
      public MathClient(grpc::CallInvoker callInvoker) : base(callInvoker)
      {
      }
      /// <summary>Protected parameterless constructor to allow creation of test doubles.</summary>
      protected MathClient() : base()
      {
      }
      /// <summary>Protected constructor to allow creation of configured clients.</summary>
      /// <param name="configuration">The client configuration.</param>
      protected MathClient(ClientBaseConfiguration configuration) : base(configuration)
      {
      }

      /// <summary>
      /// Div divides DivArgs.dividend by DivArgs.divisor and returns the quotient
      /// and remainder.
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The response received from the server.</returns>
      public virtual global::Math.DivReply Div(global::Math.DivArgs request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return Div(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Div divides DivArgs.dividend by DivArgs.divisor and returns the quotient
      /// and remainder.
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The response received from the server.</returns>
      public virtual global::Math.DivReply Div(global::Math.DivArgs request, grpc::CallOptions options)
      {
        return CallInvoker.BlockingUnaryCall(__Method_Div, null, options, request);
      }
      /// <summary>
      /// Div divides DivArgs.dividend by DivArgs.divisor and returns the quotient
      /// and remainder.
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncUnaryCall<global::Math.DivReply> DivAsync(global::Math.DivArgs request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return DivAsync(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Div divides DivArgs.dividend by DivArgs.divisor and returns the quotient
      /// and remainder.
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncUnaryCall<global::Math.DivReply> DivAsync(global::Math.DivArgs request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncUnaryCall(__Method_Div, null, options, request);
      }
      /// <summary>
      /// DivMany accepts an arbitrary number of division args from the client stream
      /// and sends back the results in the reply stream.  The stream continues until
      /// the client closes its end; the server does the same after sending all the
      /// replies.  The stream ends immediately if either end aborts.
      /// </summary>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncDuplexStreamingCall<global::Math.DivArgs, global::Math.DivReply> DivMany(grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return DivMany(new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// DivMany accepts an arbitrary number of division args from the client stream
      /// and sends back the results in the reply stream.  The stream continues until
      /// the client closes its end; the server does the same after sending all the
      /// replies.  The stream ends immediately if either end aborts.
      /// </summary>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncDuplexStreamingCall<global::Math.DivArgs, global::Math.DivReply> DivMany(grpc::CallOptions options)
      {
        return CallInvoker.AsyncDuplexStreamingCall(__Method_DivMany, null, options);
      }
      /// <summary>
      /// Fib generates numbers in the Fibonacci sequence.  If FibArgs.limit > 0, Fib
      /// generates up to limit numbers; otherwise it continues until the call is
      /// canceled.  Unlike Fib above, Fib has no final FibReply.
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncServerStreamingCall<global::Math.Num> Fib(global::Math.FibArgs request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return Fib(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Fib generates numbers in the Fibonacci sequence.  If FibArgs.limit > 0, Fib
      /// generates up to limit numbers; otherwise it continues until the call is
      /// canceled.  Unlike Fib above, Fib has no final FibReply.
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncServerStreamingCall<global::Math.Num> Fib(global::Math.FibArgs request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncServerStreamingCall(__Method_Fib, null, options, request);
      }
      /// <summary>
      /// Sum sums a stream of numbers, returning the final result once the stream
      /// is closed.
      /// </summary>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncClientStreamingCall<global::Math.Num, global::Math.Num> Sum(grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return Sum(new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      /// Sum sums a stream of numbers, returning the final result once the stream
      /// is closed.
      /// </summary>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      public virtual grpc::AsyncClientStreamingCall<global::Math.Num, global::Math.Num> Sum(grpc::CallOptions options)
      {
        return CallInvoker.AsyncClientStreamingCall(__Method_Sum, null, options);
      }
      /// <summary>Creates a new instance of client from given <c>ClientBaseConfiguration</c>.</summary>
      protected override MathClient NewInstance(ClientBaseConfiguration configuration)
      {
        return new MathClient(configuration);
      }
    }

    /// <summary>Creates service definition that can be registered with a server</summary>
    /// <param name="serviceImpl">An object implementing the server-side handling logic.</param>
    public static grpc::ServerServiceDefinition BindService(MathBase serviceImpl)
    {
      return grpc::ServerServiceDefinition.CreateBuilder()
          .AddMethod(__Method_Div, serviceImpl.Div)
          .AddMethod(__Method_DivMany, serviceImpl.DivMany)
          .AddMethod(__Method_Fib, serviceImpl.Fib)
          .AddMethod(__Method_Sum, serviceImpl.Sum).Build();
    }

    /// <summary>Register service method with a service binder without implementation. Useful when customizing the service binding logic.
    /// Note: this method is part of an experimental API that can change or be removed without any prior notice.</summary>
    /// <param name="serviceBinder">Service methods will be bound by calling <c>AddMethod</c> on this object.</param>
    public static void BindService(grpc::ServiceBinderBase serviceBinder)
    {
      serviceBinder.AddMethod(__Method_Div);
      serviceBinder.AddMethod(__Method_DivMany);
      serviceBinder.AddMethod(__Method_Fib);
      serviceBinder.AddMethod(__Method_Sum);
    }

  }
}
#endregion

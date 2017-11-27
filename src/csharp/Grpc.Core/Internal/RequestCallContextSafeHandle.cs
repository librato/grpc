#region Copyright notice and license

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

#endregion

using System;
using System.Runtime.InteropServices;
using Grpc.Core;
using Grpc.Core.Logging;

namespace Grpc.Core.Internal
{
    /// <summary>
    /// grpcsharp_request_call_context
    /// </summary>
    internal class RequestCallContextSafeHandle : SafeHandleZeroIsInvalid, IOpCompletionCallback
    {
        static readonly NativeMethods Native = NativeMethods.Get();
        static readonly ILogger Logger = GrpcEnvironment.Logger.ForType<RequestCallContextSafeHandle>();

        private RequestCallContextSafeHandle()
        {
        }

        public static RequestCallContextSafeHandle Create()
        {
            return Native.grpcsharp_request_call_context_create();
        }

        public IntPtr Handle
        {
            get
            {
                return handle;
            }
        }

        public RequestCallCompletionDelegate CompletionCallback { get; set; }

        // Gets data of server_rpc_new completion.
        public ServerRpcNew GetServerRpcNew(Server server)
        {
            var call = Native.grpcsharp_request_call_context_call(this);

            UIntPtr methodLen;
            IntPtr methodPtr = Native.grpcsharp_request_call_context_method(this, out methodLen);
            var method = Marshal.PtrToStringAnsi(methodPtr, (int) methodLen.ToUInt32());

            UIntPtr hostLen;
            IntPtr hostPtr = Native.grpcsharp_request_call_context_host(this, out hostLen);
            var host = Marshal.PtrToStringAnsi(hostPtr, (int) hostLen.ToUInt32());

            var deadline = Native.grpcsharp_request_call_context_deadline(this);

            IntPtr metadataArrayPtr = Native.grpcsharp_request_call_context_request_metadata(this);
            var metadata = MetadataArraySafeHandle.ReadMetadataFromPtrUnsafe(metadataArrayPtr);

            return new ServerRpcNew(server, call, method, host, deadline, metadata);
        }

        protected override bool ReleaseHandle()
        {
            Native.grpcsharp_request_call_context_destroy(handle);
            return true;
        }

        void IOpCompletionCallback.OnComplete(bool success)
        {
            try
            {
                CompletionCallback(success, this);
            }
            catch (Exception e)
            {
                Logger.Error(e, "Exception occured while invoking request call completion delegate.");
            }
            finally
            {
                CompletionCallback = null;
                Dispose();
            }
        }
    }
}

#region Copyright notice and license

// Copyright 2018 gRPC authors.
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
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Grpc.Core;
using Grpc.Core.Interceptors;
using Grpc.Core.Internal;
using Grpc.Core.Tests;
using Grpc.Core.Utils;
using NUnit.Framework;

namespace Grpc.Core.Interceptors.Tests
{
    public class ServerInterceptorTest
    {
        const string Host = "127.0.0.1";

        private class AddRequestHeaderServerInterceptor : GenericInterceptor
        {
            readonly Metadata.Entry header;

            public AddRequestHeaderServerInterceptor(string key, string value)
            {
                this.header = new Metadata.Entry(key, value);
            }

            protected override Task<ServerCallHooks<TRequest, TResponse>> InterceptHandler<TRequest, TResponse>(ServerCallContext context, bool clientStreaming, bool serverStreaming, TRequest request)
            {
                context.RequestHeaders.Add(header);
                return Task.FromResult<ServerCallHooks<TRequest, TResponse>>(null);
            }

            public Metadata.Entry Header => header;
        }

        [Test]
        public void AddRequestHeaderInServerInterceptor()
        {
            var helper = new MockServiceHelper(Host);
            var interceptor = new AddRequestHeaderServerInterceptor("x-interceptor", "hello world");
            helper.UnaryHandler = new UnaryServerMethod<string, string>((request, context) =>
            {
                var interceptorHeader = context.RequestHeaders.Last(m => (m.Key == interceptor.Header.Key)).Value;
                Assert.AreEqual(interceptorHeader, interceptor.Header.Value);
                return Task.FromResult("PASS");
            });
            helper.ServiceDefinition = helper.ServiceDefinition.Intercept(interceptor);
            var server = helper.GetServer();
            server.Start();
            var channel = helper.GetChannel();
            Assert.AreEqual("PASS", Calls.BlockingUnaryCall(helper.CreateUnaryCall(), ""));
        }

        private class ArbitraryActionInterceptor : GenericInterceptor
        {
            readonly Action action;

            public ArbitraryActionInterceptor(Action action)
            {
                this.action = action;
            }

            protected override Task<ServerCallHooks<TRequest, TResponse>> InterceptHandler<TRequest, TResponse>(ServerCallContext context, bool clientStreaming, bool serverStreaming, TRequest request)
            {
                action();
                return Task.FromResult<ServerCallHooks<TRequest, TResponse>>(null);
            }
        }

        [Test]
        public void VerifyInterceptorOrdering()
        {
            var helper = new MockServiceHelper(Host);
            helper.UnaryHandler = new UnaryServerMethod<string, string>((request, context) =>
            {
                return Task.FromResult("PASS");
            });
            var stringBuilder = new StringBuilder();
            helper.ServiceDefinition = helper.ServiceDefinition
                .Intercept(new ArbitraryActionInterceptor(() => stringBuilder.Append("A")))
                .Intercept(new ArbitraryActionInterceptor(() => stringBuilder.Append("B1")),
                    new ArbitraryActionInterceptor(() => stringBuilder.Append("B2")),
                    new ArbitraryActionInterceptor(() => stringBuilder.Append("B3")))
                .Intercept(new ArbitraryActionInterceptor(() => stringBuilder.Append("C")));
            var server = helper.GetServer();
            server.Start();
            var channel = helper.GetChannel();
            Assert.AreEqual("PASS", Calls.BlockingUnaryCall(helper.CreateUnaryCall(), ""));
            Assert.AreEqual("CB1B2B3A", stringBuilder.ToString());
        }

        [Test]
        public void CheckNullInterceptorRegistrationFails()
        {
            var helper = new MockServiceHelper(Host);
            helper.UnaryHandler = new UnaryServerMethod<string, string>((request, context) =>
            {
                return Task.FromResult("PASS");
            });
            var sd = helper.ServiceDefinition;
            Assert.Throws<ArgumentNullException>(() => sd.Intercept(default(Interceptor)));
            Assert.Throws<ArgumentNullException>(() => sd.Intercept(new[]{default(Interceptor)}));
            Assert.Throws<ArgumentNullException>(() => sd.Intercept(new[]{new ArbitraryActionInterceptor(()=>{}), null}));
            Assert.Throws<ArgumentNullException>(() => sd.Intercept(default(Interceptor[])));
        }
    }
}

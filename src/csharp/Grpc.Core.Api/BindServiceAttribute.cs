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

namespace Grpc.Core
{
    /// <summary>
    /// Specifies the location of the service bind method for a gRPC service.
    /// The bind method is typically generated code and is used to register a service's
    /// methods with the server on startup.
    /// 
    /// The bind method signature takes a <see cref="ServiceBinderBase"/> and an optional
    /// instance of the service base class, e.g. <c>static void BindService(ServiceBinderBase, GreeterService)</c>.
    /// </summary>
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = true)]
    public class BindServiceAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="BindServiceAttribute"/> class.
        /// </summary>
        /// <param name="bindType">The type the service bind method is defined on.</param>
        /// <param name="bindMethodName">The name of the service bind method.</param>
        public BindServiceAttribute(Type bindType, string bindMethodName)
        {
            BindType = bindType;
            BindMethodName = bindMethodName;
        }

        /// <summary>
        /// Gets the type the service bind method is defined on.
        /// </summary>
        public Type BindType { get; }

        /// <summary>
        /// Gets the name of the service bind method.
        /// </summary>
        public string BindMethodName { get; }
    }
}

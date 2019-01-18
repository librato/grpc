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

namespace Grpc.Core
{
    /// <summary>
    /// Token for propagating context of server side handlers to child calls.
    /// In situations when a backend is making calls to another backend,
    /// it makes sense to propagate properties like deadline and cancellation 
    /// token of the server call to the child call.
    /// The gRPC native layer provides some other contexts (like tracing context) that
    /// are not accessible to explicitly C# layer, but this token still allows propagating them.
    /// </summary>
    public abstract class ContextPropagationToken
    {
        internal ContextPropagationToken()
        {
        }
    }
}

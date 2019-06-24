# Copyright 2019 The gRPC Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""Server of the Python example of customizing authentication mechanism."""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import contextlib
import logging
import os
import time
from concurrent import futures

import grpc
from examples import helloworld_pb2, helloworld_pb2_grpc
from examples.python.auth import _credentials

_LOGGER = logging.getLogger(__name__)
_LOGGER.setLevel(logging.INFO)

_ONE_DAY_IN_SECONDS = 60 * 60 * 24

_LISTEN_ADDRESS_TEMPLATE = 'localhost:%d'
_SIGNATURE_HEADER_KEY = 'x-signautre'


class SignatureValidationInterceptor(grpc.ServerInterceptor):

    def __init__(self):

        def abort(ignored_request, context):
            context.abort(grpc.StatusCode.UNAUTHENTICATED, 'Invalid signature')

        self._abortion = grpc.unary_unary_rpc_method_handler(abort)

    def intercept_service(self, continuation, handler_call_details):
        # Example HandlerCallDetails object:
        #     _HandlerCallDetails(
        #       method=u'/helloworld.Greeter/SayHello',
        #       invocation_metadata=...)
        method_name = handler_call_details.method.split('/')[-1]
        expected_metadata = (_SIGNATURE_HEADER_KEY, method_name[::-1])
        if expected_metadata in handler_call_details.invocation_metadata:
            return continuation(handler_call_details)
        else:
            return self._abortion


class SimpleGreeter(helloworld_pb2_grpc.GreeterServicer):

    @staticmethod
    def SayHello(request, unused_context):
        return helloworld_pb2.HelloReply(message='Hello, %s!' % request.name)


def _load_credential_from_file(filepath):
    real_path = os.path.join(os.path.dirname(__file__), filepath)
    with open(real_path, 'r') as f:
        return f.read()


@contextlib.contextmanager
def run_server(port):
    # Bind interceptor to server
    server = grpc.server(
        futures.ThreadPoolExecutor(),
        interceptors=(SignatureValidationInterceptor(),))
    helloworld_pb2_grpc.add_GreeterServicer_to_server(SimpleGreeter(), server)

    # Loading credentials
    server_credentials = grpc.ssl_server_credentials(((
        _credentials.SERVER_CERTIFICATE_KEY,
        _credentials.SERVER_CERTIFICATE,
    ),))

    # Pass down credentails
    port = server.add_secure_port(_LISTEN_ADDRESS_TEMPLATE % port,
                                  server_credentials)

    server.start()
    yield port
    server.stop(0)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--port', nargs=1, type=int, default=50051, help='the listening port')
    args = parser.parse_args()

    with run_server(args.port) as port:
        logging.info('Server is listening at port :%d', port)
        try:
            while True:
                time.sleep(_ONE_DAY_IN_SECONDS)
        except KeyboardInterrupt:
            pass


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    main()

# Copyright the 2019 gRPC authors.
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
"""An example of cancelling requests in gRPC."""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

from concurrent import futures
import argparse
import datetime
import logging
import time
import signal
import threading

try:
    from queue import Queue
    from queue import Empty as QueueEmpty
except ImportError:
    from Queue import Queue
    from Queue import Empty as QueueEmpty

import grpc

from examples.python.cancellation import hash_name_pb2
from examples.python.cancellation import hash_name_pb2_grpc

_DESCRIPTION = "A client for finding hashes similar to names."
_LOGGER = logging.getLogger(__name__)

_TIMEOUT_SECONDS = 0.05


def run_unary_client(server_target, name, ideal_distance):
    with grpc.insecure_channel(server_target) as channel:
        stub = hash_name_pb2_grpc.HashFinderStub(channel)
        future = stub.Find.future(
            hash_name_pb2.HashNameRequest(
                desired_name=name, ideal_hamming_distance=ideal_distance))

        def cancel_request(unused_signum, unused_frame):
            future.cancel()

        signal.signal(signal.SIGINT, cancel_request)
        while True:
            try:
                result = future.result(timeout=_TIMEOUT_SECONDS)
            except grpc.FutureTimeoutError:
                continue
            except grpc.FutureCancelledError:
                break
            print(result)
            break


def run_streaming_client(server_target, name, ideal_distance,
                         interesting_distance):
    with grpc.insecure_channel(server_target) as channel:
        stub = hash_name_pb2_grpc.HashFinderStub(channel)
        result_generator = stub.FindRange(
            hash_name_pb2.HashNameRequest(
                desired_name=name,
                ideal_hamming_distance=ideal_distance,
                interesting_hamming_distance=interesting_distance))

        def cancel_request(unused_signum, unused_frame):
            result_generator.cancel()

        signal.signal(signal.SIGINT, cancel_request)
        result_queue = Queue()

        def iterate_responses(result_generator, result_queue):
            try:
                for result in result_generator:
                    result_queue.put(result)
            except grpc.RpcError as rpc_error:
                if rpc_error.code() != grpc.StatusCode.CANCELLED:
                    result_queue.put(None)
                    raise rpc_error
            # Enqueue a sentinel to signal the end of the stream.
            result_queue.put(None)

        # TODO(https://github.com/grpc/grpc/issues/19464): Do everything on the
        # main thread.
        response_thread = threading.Thread(
            target=iterate_responses, args=(result_generator, result_queue))
        response_thread.daemon = True
        response_thread.start()

        while result_generator.running():
            try:
                result = result_queue.get(timeout=_TIMEOUT_SECONDS)
            except QueueEmpty:
                continue
            if result is None:
                break
            print(result)


def main():
    parser = argparse.ArgumentParser(description=_DESCRIPTION)
    parser.add_argument("name", type=str, help='The desired name.')
    parser.add_argument(
        "--ideal-distance",
        default=0,
        nargs='?',
        type=int,
        help="The desired Hamming distance.")
    parser.add_argument(
        '--server',
        default='localhost:50051',
        type=str,
        nargs='?',
        help='The host-port pair at which to reach the server.')
    parser.add_argument(
        '--show-inferior',
        default=None,
        type=int,
        nargs='?',
        help='Also show candidates with a Hamming distance less than this value.'
    )

    args = parser.parse_args()
    if args.show_inferior is not None:
        run_streaming_client(args.server, args.name, args.ideal_distance,
                             args.show_inferior)
    else:
        run_unary_client(args.server, args.name, args.ideal_distance)


if __name__ == "__main__":
    logging.basicConfig()
    main()

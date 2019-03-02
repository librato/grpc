# Copyright 2019 gRPC authors.
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
"""An example of multiprocess concurrency with gRPC."""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

from concurrent import futures
import contextlib
import datetime
import grpc
import logging
import math
import multiprocessing
import os
import time
import socket

import prime_pb2
import prime_pb2_grpc

_ONE_DAY = datetime.timedelta(days=1)
_PROCESS_COUNT = 8
_THREAD_CONCURRENCY = 10


def is_prime(n):
    for i in range(2, int(math.ceil(math.sqrt(n)))):
        if n % i == 0:
            return False
    else:
        return True


class PrimeChecker(prime_pb2_grpc.PrimeCheckerServicer):

    def check(self, request, context):
        logging.warning(
            '[PID {}] Determining primality of {}'.format(
                    os.getpid(), request.candidate))
        return prime_pb2.Primality(isPrime=is_prime(request.candidate))


def _wait_forever(server):
    try:
        while True:
            time.sleep(_ONE_DAY.total_seconds())
    except KeyboardInterrupt:
        server.stop(None)


def _run_server(bind_address):
    """Start a server in a subprocess."""
    logging.warning( '[PID {}] Starting new server.'.format( os.getpid()))
    options = (('grpc.so_reuseport', 1),)

    # WARNING: This example takes advantage of SO_REUSEPORT. Due to the
    # limitations of manylinux1, none of our precompiled Linux wheels currently
    # support this option. (https://github.com/grpc/grpc/issues/18210). To take
    # advantage of this feature, install from source with
    # `pip install grpcio --no-binary grpcio`.

    server = grpc.server(
                futures.ThreadPoolExecutor(
                    max_workers=_THREAD_CONCURRENCY,),
                    options=options)
    prime_pb2_grpc.add_PrimeCheckerServicer_to_server(PrimeChecker(), server)
    server.add_insecure_port(bind_address)
    server.start()
    _wait_forever(server)


@contextlib.contextmanager
def _reserve_port():
    """Find and reserve a port for all subprocesses to use."""
    sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    sock.bind(('', 0))
    try:
        yield sock.getsockname()[1]
    finally:
        sock.close()


def main():
    with _reserve_port() as port:
        bind_address = '[::]:{}'.format(port)
        logging.warning("Binding to {}".format(bind_address))
        workers = []
        for _ in range(_PROCESS_COUNT):
            # NOTE: It is imperative that the worker subprocesses be forked before
            # any gRPC servers start up. See
            # https://github.com/grpc/grpc/issues/16001 for more details.
            worker = multiprocessing.Process(target=_run_server, args=(bind_address,))
            worker.start()
            workers.append(worker)
        for worker in workers:
            worker.join()


if __name__ == '__main__':
    logging.basicConfig()
    main()

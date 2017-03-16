/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

'use strict';

var path = require('path');
var fs = require('fs');

var SSL_ROOTS_PATH = path.resolve(__dirname, '..', '..', 'etc', 'roots.pem');

var _ = require('lodash');

var ProtoBuf = require('protobufjs');

var client = require('./src/client.js');

var server = require('./src/server.js');

var common = require('./src/common.js');

var Metadata = require('./src/metadata.js');

var grpc = require('./src/grpc_extension');

var protobuf_js_5_common = require('./src/protobuf_js_5_common');
var protobuf_js_6_common = require('./src/protobuf_js_6_common');

grpc.setDefaultRootsPem(fs.readFileSync(SSL_ROOTS_PATH, 'ascii'));

exports.loadObject = function loadObject(value, options) {
  options = _.defaults(options, {'protobufjs_version': 5});
  switch (options.protobufjs_version) {
    case 5: return protobuf_js_5_common.loadObject(value, options);
    case 6: return protobuf_js_6_common.loadObject(value, options);
    default: throw new Error('Unrecognized protobufjs_version:',
                             options.protobufjs_version);
  }
};

var loadObject = exports.loadObject;

function applyProtoRoot(filename, root) {
  if (_.isString(filename)) {
    return filename;
  }
  filename.root = path.resolve(filename.root) + '/';
  root.resolvePath = function(originPath, importPath, alreadyNormalized) {
    return ProtoBuf.util.path.resolve(filename.root,
                                      importPath,
                                      alreadyNormalized);
  };
  return filename.file;
}

/**
 * Load a gRPC object from a .proto file. The options object can provide the
 * following options:
 * - convertFieldsToCamelCase: Loads this file with that option on protobuf.js
 *   set as specified. See
 *   https://github.com/dcodeIO/protobuf.js/wiki/Advanced-options for details
 * - binaryAsBase64: deserialize bytes values as base64 strings instead of
 *   Buffers. Defaults to false
 * - longsAsStrings: deserialize long values as strings instead of objects.
 *   Defaults to true
 * - deprecatedArgumentOrder: Use the beta method argument order for client
 *   methods, with optional arguments after the callback. Defaults to false.
 *   This option is only a temporary stopgap measure to smooth an API breakage.
 *   It is deprecated, and new code should not use it.
 * @param {string|{root: string, file: string}} filename The file to load
 * @param {string=} format The file format to expect. Must be either 'proto' or
 *     'json'. Defaults to 'proto'
 * @param {Object=} options Options to apply to the loaded file
 * @return {Object<string, *>} The resulting gRPC object
 */
exports.load = function load(filename, format, options) {
  /* Note: format is currently unused, because the API for loading a proto
     file or a JSON file is identical in Protobuf.js 6. In the future, there is
     still the possibility of adding other formats that would be loaded
     differently */
  options = _.defaults(options, common.defaultGrpcOptions);
  options.protobufjs_version = 6;
  var root = new ProtoBuf.Root();
  var parse_options = {keepCase: !options.convertFieldsToCamelCase};
  return loadObject(root.loadSync(applyProtoRoot(filename, root),
                                  parse_options),
                    options);
};

var log_template = _.template(
    '{severity} {timestamp}\t{file}:{line}]\t{message}',
    {interpolate: /{([\s\S]+?)}/g});

/**
 * Sets the logger function for the gRPC module. For debugging purposes, the C
 * core will log synchronously directly to stdout unless this function is
 * called. Note: the output format here is intended to be informational, and
 * is not guaranteed to stay the same in the future.
 * Logs will be directed to logger.error.
 * @param {Console} logger A Console-like object.
 */
exports.setLogger = function setLogger(logger) {
  common.logger = logger;
  grpc.setDefaultLoggerCallback(function(file, line, severity,
                                         message, timestamp) {
    logger.error(log_template({
      file: path.basename(file),
      line: line,
      severity: severity,
      message: message,
      timestamp: timestamp.toISOString()
    }));
  });
};

/**
 * Sets the logger verbosity for gRPC module logging. The options are members
 * of the grpc.logVerbosity map.
 * @param {Number} verbosity The minimum severity to log
 */
exports.setLogVerbosity = function setLogVerbosity(verbosity) {
  common.logVerbosity = verbosity;
  grpc.setLogVerbosity(verbosity);
};

/**
 * @see module:src/server.Server
 */
exports.Server = server.Server;

/**
 * @see module:src/metadata
 */
exports.Metadata = Metadata;

/**
 * Status name to code number mapping
 */
exports.status = grpc.status;

/**
 * Propagate flag name to number mapping
 */
exports.propagate = grpc.propagate;

/**
 * Call error name to code number mapping
 */
exports.callError = grpc.callError;

/**
 * Write flag name to code number mapping
 */
exports.writeFlags = grpc.writeFlags;

/**
 * Log verbosity setting name to code number mapping
 */
exports.logVerbosity = grpc.logVerbosity;

/**
 * Credentials factories
 */
exports.credentials = require('./src/credentials.js');

/**
 * ServerCredentials factories
 */
exports.ServerCredentials = grpc.ServerCredentials;

/**
 * @see module:src/client.makeClientConstructor
 */
exports.makeGenericClientConstructor = client.makeClientConstructor;

/**
 * @see module:src/client.getClientChannel
 */
exports.getClientChannel = client.getClientChannel;

/**
 * @see module:src/client.waitForClientReady
 */
exports.waitForClientReady = client.waitForClientReady;

exports.closeClient = function closeClient(client_obj) {
  client.getClientChannel(client_obj).close();
};

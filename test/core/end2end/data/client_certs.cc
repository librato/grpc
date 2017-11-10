/*
 *
 * Copyright 2016 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

extern "C" const char test_self_signed_client_cert[] = {
    0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e, 0x20, 0x43,
    0x45, 0x52, 0x54, 0x49, 0x46, 0x49, 0x43, 0x41, 0x54, 0x45, 0x2d, 0x2d,
    0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49, 0x49, 0x43, 0x6f, 0x44, 0x43, 0x43,
    0x41, 0x67, 0x6d, 0x67, 0x41, 0x77, 0x49, 0x42, 0x41, 0x67, 0x49, 0x4a,
    0x41, 0x4e, 0x49, 0x7a, 0x32, 0x2f, 0x7a, 0x6f, 0x52, 0x69, 0x61, 0x70,
    0x4d, 0x41, 0x30, 0x47, 0x43, 0x53, 0x71, 0x47, 0x53, 0x49, 0x62, 0x33,
    0x44, 0x51, 0x45, 0x42, 0x42, 0x51, 0x55, 0x41, 0x4d, 0x47, 0x6b, 0x78,
    0x43, 0x7a, 0x41, 0x4a, 0x42, 0x67, 0x4e, 0x56, 0x0a, 0x42, 0x41, 0x59,
    0x54, 0x41, 0x6b, 0x46, 0x56, 0x4d, 0x52, 0x4d, 0x77, 0x45, 0x51, 0x59,
    0x44, 0x56, 0x51, 0x51, 0x49, 0x44, 0x41, 0x70, 0x54, 0x62, 0x32, 0x31,
    0x6c, 0x4c, 0x56, 0x4e, 0x30, 0x59, 0x58, 0x52, 0x6c, 0x4d, 0x53, 0x45,
    0x77, 0x48, 0x77, 0x59, 0x44, 0x56, 0x51, 0x51, 0x4b, 0x44, 0x42, 0x68,
    0x4a, 0x62, 0x6e, 0x52, 0x6c, 0x63, 0x6d, 0x35, 0x6c, 0x64, 0x43, 0x42,
    0x58, 0x0a, 0x61, 0x57, 0x52, 0x6e, 0x61, 0x58, 0x52, 0x7a, 0x49, 0x46,
    0x42, 0x30, 0x65, 0x53, 0x42, 0x4d, 0x64, 0x47, 0x51, 0x78, 0x49, 0x6a,
    0x41, 0x67, 0x42, 0x67, 0x4e, 0x56, 0x42, 0x41, 0x4d, 0x4d, 0x47, 0x57,
    0x4a, 0x68, 0x5a, 0x47, 0x4e, 0x73, 0x61, 0x57, 0x56, 0x75, 0x64, 0x43,
    0x35, 0x30, 0x5a, 0x58, 0x4e, 0x30, 0x4c, 0x6d, 0x64, 0x76, 0x62, 0x32,
    0x64, 0x73, 0x5a, 0x53, 0x35, 0x6a, 0x0a, 0x62, 0x32, 0x30, 0x77, 0x48,
    0x68, 0x63, 0x4e, 0x4d, 0x54, 0x51, 0x77, 0x4e, 0x7a, 0x49, 0x34, 0x4d,
    0x6a, 0x41, 0x77, 0x4f, 0x44, 0x49, 0x31, 0x57, 0x68, 0x63, 0x4e, 0x4d,
    0x6a, 0x51, 0x77, 0x4e, 0x7a, 0x49, 0x31, 0x4d, 0x6a, 0x41, 0x77, 0x4f,
    0x44, 0x49, 0x31, 0x57, 0x6a, 0x42, 0x70, 0x4d, 0x51, 0x73, 0x77, 0x43,
    0x51, 0x59, 0x44, 0x56, 0x51, 0x51, 0x47, 0x45, 0x77, 0x4a, 0x42, 0x0a,
    0x56, 0x54, 0x45, 0x54, 0x4d, 0x42, 0x45, 0x47, 0x41, 0x31, 0x55, 0x45,
    0x43, 0x41, 0x77, 0x4b, 0x55, 0x32, 0x39, 0x74, 0x5a, 0x53, 0x31, 0x54,
    0x64, 0x47, 0x46, 0x30, 0x5a, 0x54, 0x45, 0x68, 0x4d, 0x42, 0x38, 0x47,
    0x41, 0x31, 0x55, 0x45, 0x43, 0x67, 0x77, 0x59, 0x53, 0x57, 0x35, 0x30,
    0x5a, 0x58, 0x4a, 0x75, 0x5a, 0x58, 0x51, 0x67, 0x56, 0x32, 0x6c, 0x6b,
    0x5a, 0x32, 0x6c, 0x30, 0x0a, 0x63, 0x79, 0x42, 0x51, 0x64, 0x48, 0x6b,
    0x67, 0x54, 0x48, 0x52, 0x6b, 0x4d, 0x53, 0x49, 0x77, 0x49, 0x41, 0x59,
    0x44, 0x56, 0x51, 0x51, 0x44, 0x44, 0x42, 0x6c, 0x69, 0x59, 0x57, 0x52,
    0x6a, 0x62, 0x47, 0x6c, 0x6c, 0x62, 0x6e, 0x51, 0x75, 0x64, 0x47, 0x56,
    0x7a, 0x64, 0x43, 0x35, 0x6e, 0x62, 0x32, 0x39, 0x6e, 0x62, 0x47, 0x55,
    0x75, 0x59, 0x32, 0x39, 0x74, 0x4d, 0x49, 0x47, 0x66, 0x0a, 0x4d, 0x41,
    0x30, 0x47, 0x43, 0x53, 0x71, 0x47, 0x53, 0x49, 0x62, 0x33, 0x44, 0x51,
    0x45, 0x42, 0x41, 0x51, 0x55, 0x41, 0x41, 0x34, 0x47, 0x4e, 0x41, 0x44,
    0x43, 0x42, 0x69, 0x51, 0x4b, 0x42, 0x67, 0x51, 0x43, 0x79, 0x58, 0x32,
    0x4a, 0x78, 0x5a, 0x2b, 0x4a, 0x35, 0x49, 0x2b, 0x64, 0x6c, 0x68, 0x52,
    0x4f, 0x56, 0x74, 0x71, 0x6c, 0x4d, 0x51, 0x6e, 0x34, 0x37, 0x42, 0x42,
    0x63, 0x72, 0x0a, 0x6c, 0x32, 0x47, 0x43, 0x6b, 0x76, 0x39, 0x4f, 0x31,
    0x44, 0x31, 0x72, 0x4c, 0x39, 0x34, 0x4b, 0x57, 0x59, 0x62, 0x59, 0x31,
    0x34, 0x48, 0x58, 0x68, 0x69, 0x2f, 0x6e, 0x61, 0x63, 0x42, 0x41, 0x51,
    0x74, 0x43, 0x45, 0x51, 0x77, 0x58, 0x78, 0x70, 0x35, 0x44, 0x4b, 0x65,
    0x6d, 0x47, 0x4f, 0x55, 0x6a, 0x75, 0x36, 0x35, 0x78, 0x4d, 0x39, 0x46,
    0x39, 0x36, 0x2f, 0x33, 0x37, 0x34, 0x47, 0x0a, 0x4d, 0x76, 0x6e, 0x52,
    0x4a, 0x64, 0x6f, 0x35, 0x32, 0x67, 0x4f, 0x73, 0x34, 0x48, 0x4f, 0x30,
    0x63, 0x7a, 0x42, 0x70, 0x66, 0x56, 0x4e, 0x64, 0x58, 0x65, 0x65, 0x6f,
    0x44, 0x2f, 0x52, 0x59, 0x67, 0x77, 0x74, 0x74, 0x66, 0x64, 0x4a, 0x72,
    0x7a, 0x2f, 0x34, 0x61, 0x61, 0x74, 0x73, 0x53, 0x32, 0x51, 0x6b, 0x32,
    0x79, 0x4d, 0x59, 0x70, 0x71, 0x5a, 0x6d, 0x71, 0x45, 0x4d, 0x73, 0x62,
    0x0a, 0x72, 0x68, 0x39, 0x57, 0x32, 0x32, 0x4c, 0x70, 0x33, 0x72, 0x43,
    0x42, 0x76, 0x77, 0x49, 0x44, 0x41, 0x51, 0x41, 0x42, 0x6f, 0x31, 0x41,
    0x77, 0x54, 0x6a, 0x41, 0x64, 0x42, 0x67, 0x4e, 0x56, 0x48, 0x51, 0x34,
    0x45, 0x46, 0x67, 0x51, 0x55, 0x35, 0x32, 0x33, 0x41, 0x4a, 0x4d, 0x52,
    0x38, 0x44, 0x73, 0x39, 0x56, 0x38, 0x66, 0x68, 0x66, 0x37, 0x67, 0x75,
    0x31, 0x69, 0x30, 0x4d, 0x4d, 0x0a, 0x55, 0x71, 0x41, 0x77, 0x48, 0x77,
    0x59, 0x44, 0x56, 0x52, 0x30, 0x6a, 0x42, 0x42, 0x67, 0x77, 0x46, 0x6f,
    0x41, 0x55, 0x35, 0x32, 0x33, 0x41, 0x4a, 0x4d, 0x52, 0x38, 0x44, 0x73,
    0x39, 0x56, 0x38, 0x66, 0x68, 0x66, 0x37, 0x67, 0x75, 0x31, 0x69, 0x30,
    0x4d, 0x4d, 0x55, 0x71, 0x41, 0x77, 0x44, 0x41, 0x59, 0x44, 0x56, 0x52,
    0x30, 0x54, 0x42, 0x41, 0x55, 0x77, 0x41, 0x77, 0x45, 0x42, 0x0a, 0x2f,
    0x7a, 0x41, 0x4e, 0x42, 0x67, 0x6b, 0x71, 0x68, 0x6b, 0x69, 0x47, 0x39,
    0x77, 0x30, 0x42, 0x41, 0x51, 0x55, 0x46, 0x41, 0x41, 0x4f, 0x42, 0x67,
    0x51, 0x43, 0x49, 0x2f, 0x74, 0x76, 0x53, 0x42, 0x59, 0x48, 0x31, 0x69,
    0x79, 0x66, 0x4c, 0x61, 0x43, 0x54, 0x42, 0x4b, 0x77, 0x70, 0x64, 0x6a,
    0x33, 0x36, 0x2b, 0x4d, 0x6b, 0x52, 0x39, 0x45, 0x65, 0x4a, 0x4a, 0x6d,
    0x49, 0x6d, 0x78, 0x0a, 0x58, 0x2b, 0x62, 0x6a, 0x68, 0x4b, 0x57, 0x58,
    0x77, 0x73, 0x42, 0x58, 0x34, 0x50, 0x44, 0x4d, 0x57, 0x76, 0x64, 0x75,
    0x73, 0x72, 0x2b, 0x2b, 0x51, 0x47, 0x55, 0x59, 0x74, 0x79, 0x6f, 0x79,
    0x61, 0x2b, 0x68, 0x66, 0x59, 0x4d, 0x58, 0x52, 0x68, 0x58, 0x75, 0x61,
    0x33, 0x39, 0x6d, 0x44, 0x35, 0x34, 0x78, 0x67, 0x6c, 0x6f, 0x51, 0x4e,
    0x75, 0x75, 0x39, 0x52, 0x45, 0x44, 0x77, 0x58, 0x0a, 0x46, 0x66, 0x74,
    0x6f, 0x2b, 0x61, 0x4f, 0x77, 0x33, 0x42, 0x63, 0x59, 0x64, 0x75, 0x63,
    0x7a, 0x36, 0x6f, 0x66, 0x78, 0x69, 0x63, 0x46, 0x4b, 0x2f, 0x59, 0x32,
    0x56, 0x65, 0x58, 0x44, 0x75, 0x72, 0x53, 0x4d, 0x70, 0x52, 0x76, 0x35,
    0x54, 0x66, 0x47, 0x66, 0x32, 0x51, 0x72, 0x36, 0x65, 0x4f, 0x4f, 0x64,
    0x61, 0x52, 0x68, 0x6a, 0x36, 0x65, 0x64, 0x37, 0x42, 0x69, 0x62, 0x48,
    0x6b, 0x0a, 0x58, 0x31, 0x56, 0x47, 0x5a, 0x41, 0x3d, 0x3d, 0x0a, 0x2d,
    0x2d, 0x2d, 0x2d, 0x2d, 0x45, 0x4e, 0x44, 0x20, 0x43, 0x45, 0x52, 0x54,
    0x49, 0x46, 0x49, 0x43, 0x41, 0x54, 0x45, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d,
    0x0a, 0x00};

extern "C" const char test_self_signed_client_key[] = {
    0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e, 0x20, 0x50,
    0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b, 0x45, 0x59, 0x2d, 0x2d,
    0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49, 0x49, 0x43, 0x64, 0x77, 0x49, 0x42,
    0x41, 0x44, 0x41, 0x4e, 0x42, 0x67, 0x6b, 0x71, 0x68, 0x6b, 0x69, 0x47,
    0x39, 0x77, 0x30, 0x42, 0x41, 0x51, 0x45, 0x46, 0x41, 0x41, 0x53, 0x43,
    0x41, 0x6d, 0x45, 0x77, 0x67, 0x67, 0x4a, 0x64, 0x41, 0x67, 0x45, 0x41,
    0x41, 0x6f, 0x47, 0x42, 0x41, 0x4c, 0x4a, 0x66, 0x59, 0x6e, 0x46, 0x6e,
    0x34, 0x6e, 0x6b, 0x6a, 0x35, 0x32, 0x57, 0x46, 0x0a, 0x45, 0x35, 0x57,
    0x32, 0x71, 0x55, 0x78, 0x43, 0x66, 0x6a, 0x73, 0x45, 0x46, 0x79, 0x75,
    0x58, 0x59, 0x59, 0x4b, 0x53, 0x2f, 0x30, 0x37, 0x55, 0x50, 0x57, 0x73,
    0x76, 0x33, 0x67, 0x70, 0x5a, 0x68, 0x74, 0x6a, 0x58, 0x67, 0x64, 0x65,
    0x47, 0x4c, 0x2b, 0x64, 0x70, 0x77, 0x45, 0x42, 0x43, 0x30, 0x49, 0x52,
    0x44, 0x42, 0x66, 0x47, 0x6e, 0x6b, 0x4d, 0x70, 0x36, 0x59, 0x59, 0x35,
    0x53, 0x0a, 0x4f, 0x37, 0x72, 0x6e, 0x45, 0x7a, 0x30, 0x58, 0x33, 0x72,
    0x2f, 0x66, 0x76, 0x67, 0x59, 0x79, 0x2b, 0x64, 0x45, 0x6c, 0x32, 0x6a,
    0x6e, 0x61, 0x41, 0x36, 0x7a, 0x67, 0x63, 0x37, 0x52, 0x7a, 0x4d, 0x47,
    0x6c, 0x39, 0x55, 0x31, 0x31, 0x64, 0x35, 0x36, 0x67, 0x50, 0x39, 0x46,
    0x69, 0x44, 0x43, 0x32, 0x31, 0x39, 0x30, 0x6d, 0x76, 0x50, 0x2f, 0x68,
    0x70, 0x71, 0x32, 0x78, 0x4c, 0x5a, 0x0a, 0x43, 0x54, 0x62, 0x49, 0x78,
    0x69, 0x6d, 0x70, 0x6d, 0x61, 0x6f, 0x51, 0x79, 0x78, 0x75, 0x75, 0x48,
    0x31, 0x62, 0x62, 0x59, 0x75, 0x6e, 0x65, 0x73, 0x49, 0x47, 0x2f, 0x41,
    0x67, 0x4d, 0x42, 0x41, 0x41, 0x45, 0x43, 0x67, 0x59, 0x41, 0x64, 0x71,
    0x4a, 0x43, 0x45, 0x7a, 0x4d, 0x49, 0x79, 0x5a, 0x45, 0x37, 0x6f, 0x61,
    0x57, 0x30, 0x74, 0x4f, 0x70, 0x63, 0x42, 0x30, 0x42, 0x69, 0x50, 0x0a,
    0x46, 0x59, 0x6f, 0x49, 0x76, 0x48, 0x34, 0x42, 0x4b, 0x52, 0x48, 0x38,
    0x65, 0x48, 0x76, 0x52, 0x34, 0x37, 0x36, 0x6d, 0x74, 0x2b, 0x59, 0x64,
    0x44, 0x68, 0x42, 0x50, 0x31, 0x73, 0x63, 0x47, 0x55, 0x6d, 0x59, 0x65,
    0x43, 0x54, 0x34, 0x45, 0x6a, 0x2b, 0x52, 0x67, 0x48, 0x76, 0x32, 0x4c,
    0x50, 0x54, 0x67, 0x56, 0x59, 0x77, 0x54, 0x39, 0x65, 0x63, 0x69, 0x50,
    0x32, 0x2b, 0x45, 0x2f, 0x0a, 0x43, 0x42, 0x43, 0x4e, 0x52, 0x65, 0x6c,
    0x30, 0x53, 0x77, 0x39, 0x4a, 0x65, 0x70, 0x77, 0x57, 0x30, 0x72, 0x2b,
    0x6a, 0x57, 0x4a, 0x74, 0x44, 0x59, 0x31, 0x70, 0x70, 0x36, 0x59, 0x58,
    0x41, 0x67, 0x4e, 0x52, 0x47, 0x58, 0x32, 0x55, 0x66, 0x6c, 0x76, 0x55,
    0x73, 0x54, 0x2b, 0x6f, 0x39, 0x6c, 0x5a, 0x76, 0x61, 0x67, 0x66, 0x39,
    0x6d, 0x6f, 0x4c, 0x54, 0x4d, 0x79, 0x47, 0x76, 0x55, 0x0a, 0x75, 0x4c,
    0x46, 0x6e, 0x73, 0x79, 0x66, 0x4c, 0x69, 0x6d, 0x31, 0x42, 0x34, 0x76,
    0x58, 0x76, 0x57, 0x51, 0x4a, 0x42, 0x41, 0x4e, 0x6f, 0x75, 0x5a, 0x6c,
    0x6c, 0x58, 0x47, 0x5a, 0x6f, 0x53, 0x72, 0x5a, 0x4c, 0x74, 0x52, 0x33,
    0x56, 0x67, 0x56, 0x34, 0x74, 0x7a, 0x52, 0x51, 0x76, 0x4a, 0x78, 0x75,
    0x38, 0x34, 0x6b, 0x4c, 0x65, 0x49, 0x6b, 0x36, 0x34, 0x4f, 0x76, 0x34,
    0x37, 0x58, 0x0a, 0x70, 0x48, 0x56, 0x42, 0x4d, 0x54, 0x52, 0x42, 0x66,
    0x7a, 0x50, 0x45, 0x68, 0x62, 0x42, 0x6f, 0x64, 0x6a, 0x72, 0x31, 0x6d,
    0x35, 0x4f, 0x4c, 0x61, 0x56, 0x4c, 0x71, 0x6b, 0x46, 0x63, 0x58, 0x66,
    0x74, 0x7a, 0x52, 0x43, 0x72, 0x62, 0x57, 0x6f, 0x4b, 0x73, 0x43, 0x51,
    0x51, 0x44, 0x52, 0x53, 0x6f, 0x4c, 0x4c, 0x58, 0x4f, 0x69, 0x4c, 0x72,
    0x74, 0x4a, 0x33, 0x44, 0x4c, 0x4a, 0x43, 0x0a, 0x72, 0x58, 0x37, 0x59,
    0x38, 0x77, 0x72, 0x48, 0x5a, 0x72, 0x71, 0x6b, 0x35, 0x62, 0x4d, 0x64,
    0x5a, 0x4c, 0x47, 0x61, 0x2f, 0x55, 0x58, 0x38, 0x52, 0x61, 0x6e, 0x68,
    0x56, 0x77, 0x33, 0x2b, 0x58, 0x70, 0x2b, 0x75, 0x72, 0x64, 0x31, 0x37,
    0x31, 0x31, 0x75, 0x6d, 0x65, 0x4e, 0x4a, 0x66, 0x7a, 0x75, 0x2f, 0x4d,
    0x43, 0x6b, 0x34, 0x61, 0x31, 0x4b, 0x6b, 0x47, 0x2f, 0x43, 0x55, 0x30,
    0x0a, 0x72, 0x71, 0x73, 0x39, 0x41, 0x6b, 0x41, 0x34, 0x63, 0x53, 0x78,
    0x31, 0x44, 0x44, 0x31, 0x4a, 0x53, 0x47, 0x2b, 0x79, 0x78, 0x4d, 0x4e,
    0x70, 0x73, 0x41, 0x53, 0x31, 0x78, 0x4a, 0x6f, 0x6d, 0x46, 0x49, 0x72,
    0x73, 0x4d, 0x39, 0x76, 0x73, 0x50, 0x74, 0x37, 0x46, 0x64, 0x6e, 0x64,
    0x44, 0x77, 0x72, 0x46, 0x2b, 0x79, 0x2b, 0x43, 0x6f, 0x76, 0x68, 0x44,
    0x6b, 0x47, 0x59, 0x44, 0x6b, 0x0a, 0x52, 0x41, 0x48, 0x68, 0x2b, 0x73,
    0x76, 0x47, 0x66, 0x5a, 0x67, 0x2f, 0x70, 0x51, 0x4b, 0x32, 0x4a, 0x52,
    0x50, 0x69, 0x6d, 0x41, 0x6d, 0x48, 0x68, 0x7a, 0x71, 0x46, 0x41, 0x6b,
    0x45, 0x41, 0x75, 0x36, 0x59, 0x61, 0x37, 0x30, 0x73, 0x32, 0x46, 0x55,
    0x65, 0x42, 0x33, 0x4d, 0x75, 0x39, 0x61, 0x4a, 0x73, 0x32, 0x43, 0x44,
    0x36, 0x68, 0x67, 0x33, 0x64, 0x51, 0x45, 0x56, 0x6b, 0x42, 0x0a, 0x35,
    0x33, 0x44, 0x49, 0x37, 0x54, 0x58, 0x34, 0x38, 0x64, 0x39, 0x6b, 0x47,
    0x57, 0x35, 0x38, 0x56, 0x58, 0x31, 0x78, 0x6e, 0x71, 0x53, 0x30, 0x32,
    0x4c, 0x79, 0x57, 0x71, 0x41, 0x50, 0x63, 0x57, 0x35, 0x71, 0x6d, 0x31,
    0x6b, 0x4c, 0x48, 0x46, 0x4c, 0x64, 0x6e, 0x64, 0x61, 0x50, 0x4e, 0x6d,
    0x42, 0x61, 0x6a, 0x34, 0x51, 0x4a, 0x42, 0x41, 0x4a, 0x75, 0x67, 0x6c,
    0x33, 0x36, 0x37, 0x0a, 0x39, 0x64, 0x39, 0x74, 0x2f, 0x51, 0x4c, 0x54,
    0x53, 0x75, 0x55, 0x4c, 0x4c, 0x61, 0x6f, 0x59, 0x76, 0x32, 0x76, 0x4a,
    0x54, 0x33, 0x73, 0x31, 0x79, 0x39, 0x48, 0x4e, 0x38, 0x39, 0x45, 0x6f,
    0x61, 0x44, 0x44, 0x45, 0x6b, 0x50, 0x56, 0x66, 0x51, 0x75, 0x36, 0x47,
    0x56, 0x45, 0x58, 0x67, 0x49, 0x42, 0x74, 0x69, 0x6d, 0x31, 0x73, 0x49,
    0x2f, 0x56, 0x50, 0x53, 0x7a, 0x49, 0x38, 0x48, 0x0a, 0x61, 0x58, 0x76,
    0x61, 0x54, 0x55, 0x77, 0x62, 0x6c, 0x46, 0x57, 0x53, 0x4d, 0x37, 0x30,
    0x3d, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x45, 0x4e, 0x44, 0x20, 0x50,
    0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b, 0x45, 0x59, 0x2d, 0x2d,
    0x2d, 0x2d, 0x2d, 0x0a, 0x00};

extern "C" const char test_signed_client_cert[] = {
    0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e, 0x20, 0x43,
    0x45, 0x52, 0x54, 0x49, 0x46, 0x49, 0x43, 0x41, 0x54, 0x45, 0x2d, 0x2d,
    0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49, 0x49, 0x43, 0x48, 0x7a, 0x43, 0x43,
    0x41, 0x59, 0x67, 0x43, 0x41, 0x51, 0x45, 0x77, 0x44, 0x51, 0x59, 0x4a,
    0x4b, 0x6f, 0x5a, 0x49, 0x68, 0x76, 0x63, 0x4e, 0x41, 0x51, 0x45, 0x46,
    0x42, 0x51, 0x41, 0x77, 0x56, 0x6a, 0x45, 0x4c, 0x4d, 0x41, 0x6b, 0x47,
    0x41, 0x31, 0x55, 0x45, 0x42, 0x68, 0x4d, 0x43, 0x51, 0x56, 0x55, 0x78,
    0x45, 0x7a, 0x41, 0x52, 0x42, 0x67, 0x4e, 0x56, 0x0a, 0x42, 0x41, 0x67,
    0x4d, 0x43, 0x6c, 0x4e, 0x76, 0x62, 0x57, 0x55, 0x74, 0x55, 0x33, 0x52,
    0x68, 0x64, 0x47, 0x55, 0x78, 0x49, 0x54, 0x41, 0x66, 0x42, 0x67, 0x4e,
    0x56, 0x42, 0x41, 0x6f, 0x4d, 0x47, 0x45, 0x6c, 0x75, 0x64, 0x47, 0x56,
    0x79, 0x62, 0x6d, 0x56, 0x30, 0x49, 0x46, 0x64, 0x70, 0x5a, 0x47, 0x64,
    0x70, 0x64, 0x48, 0x4d, 0x67, 0x55, 0x48, 0x52, 0x35, 0x49, 0x45, 0x78,
    0x30, 0x0a, 0x5a, 0x44, 0x45, 0x50, 0x4d, 0x41, 0x30, 0x47, 0x41, 0x31,
    0x55, 0x45, 0x41, 0x77, 0x77, 0x47, 0x64, 0x47, 0x56, 0x7a, 0x64, 0x47,
    0x4e, 0x68, 0x4d, 0x42, 0x34, 0x58, 0x44, 0x54, 0x45, 0x30, 0x4d, 0x44,
    0x63, 0x78, 0x4e, 0x7a, 0x49, 0x7a, 0x4e, 0x54, 0x59, 0x77, 0x4d, 0x6c,
    0x6f, 0x58, 0x44, 0x54, 0x49, 0x30, 0x4d, 0x44, 0x63, 0x78, 0x4e, 0x44,
    0x49, 0x7a, 0x4e, 0x54, 0x59, 0x77, 0x0a, 0x4d, 0x6c, 0x6f, 0x77, 0x57,
    0x6a, 0x45, 0x4c, 0x4d, 0x41, 0x6b, 0x47, 0x41, 0x31, 0x55, 0x45, 0x42,
    0x68, 0x4d, 0x43, 0x51, 0x56, 0x55, 0x78, 0x45, 0x7a, 0x41, 0x52, 0x42,
    0x67, 0x4e, 0x56, 0x42, 0x41, 0x67, 0x4d, 0x43, 0x6c, 0x4e, 0x76, 0x62,
    0x57, 0x55, 0x74, 0x55, 0x33, 0x52, 0x68, 0x64, 0x47, 0x55, 0x78, 0x49,
    0x54, 0x41, 0x66, 0x42, 0x67, 0x4e, 0x56, 0x42, 0x41, 0x6f, 0x4d, 0x0a,
    0x47, 0x45, 0x6c, 0x75, 0x64, 0x47, 0x56, 0x79, 0x62, 0x6d, 0x56, 0x30,
    0x49, 0x46, 0x64, 0x70, 0x5a, 0x47, 0x64, 0x70, 0x64, 0x48, 0x4d, 0x67,
    0x55, 0x48, 0x52, 0x35, 0x49, 0x45, 0x78, 0x30, 0x5a, 0x44, 0x45, 0x54,
    0x4d, 0x42, 0x45, 0x47, 0x41, 0x31, 0x55, 0x45, 0x41, 0x77, 0x77, 0x4b,
    0x64, 0x47, 0x56, 0x7a, 0x64, 0x47, 0x4e, 0x73, 0x61, 0x57, 0x56, 0x75,
    0x64, 0x44, 0x43, 0x42, 0x0a, 0x6e, 0x7a, 0x41, 0x4e, 0x42, 0x67, 0x6b,
    0x71, 0x68, 0x6b, 0x69, 0x47, 0x39, 0x77, 0x30, 0x42, 0x41, 0x51, 0x45,
    0x46, 0x41, 0x41, 0x4f, 0x42, 0x6a, 0x51, 0x41, 0x77, 0x67, 0x59, 0x6b,
    0x43, 0x67, 0x59, 0x45, 0x41, 0x37, 0x46, 0x52, 0x48, 0x32, 0x36, 0x47,
    0x2b, 0x46, 0x74, 0x35, 0x56, 0x51, 0x67, 0x79, 0x7a, 0x6c, 0x5a, 0x73,
    0x66, 0x53, 0x6e, 0x48, 0x53, 0x5a, 0x36, 0x47, 0x58, 0x0a, 0x62, 0x37,
    0x71, 0x78, 0x6d, 0x6b, 0x32, 0x50, 0x4f, 0x38, 0x54, 0x59, 0x71, 0x4b,
    0x5a, 0x6d, 0x6b, 0x66, 0x4d, 0x77, 0x6b, 0x65, 0x36, 0x52, 0x55, 0x66,
    0x51, 0x56, 0x2b, 0x53, 0x2b, 0x47, 0x7a, 0x52, 0x76, 0x7a, 0x35, 0x4c,
    0x6c, 0x53, 0x33, 0x31, 0x55, 0x31, 0x51, 0x43, 0x70, 0x33, 0x63, 0x67,
    0x77, 0x6b, 0x49, 0x49, 0x41, 0x51, 0x61, 0x31, 0x45, 0x32, 0x68, 0x43,
    0x45, 0x7a, 0x0a, 0x57, 0x33, 0x31, 0x69, 0x76, 0x62, 0x4d, 0x42, 0x79,
    0x52, 0x4b, 0x39, 0x74, 0x46, 0x70, 0x79, 0x6e, 0x34, 0x55, 0x76, 0x38,
    0x4b, 0x50, 0x31, 0x34, 0x4f, 0x62, 0x4b, 0x6a, 0x54, 0x51, 0x71, 0x78,
    0x55, 0x5a, 0x70, 0x35, 0x35, 0x38, 0x44, 0x67, 0x4f, 0x48, 0x67, 0x35,
    0x62, 0x35, 0x6d, 0x47, 0x52, 0x4d, 0x30, 0x70, 0x79, 0x56, 0x31, 0x65,
    0x71, 0x52, 0x4b, 0x36, 0x50, 0x57, 0x77, 0x0a, 0x52, 0x2f, 0x62, 0x6a,
    0x67, 0x6c, 0x6c, 0x69, 0x36, 0x70, 0x6d, 0x6e, 0x72, 0x2b, 0x30, 0x43,
    0x41, 0x77, 0x45, 0x41, 0x41, 0x54, 0x41, 0x4e, 0x42, 0x67, 0x6b, 0x71,
    0x68, 0x6b, 0x69, 0x47, 0x39, 0x77, 0x30, 0x42, 0x41, 0x51, 0x55, 0x46,
    0x41, 0x41, 0x4f, 0x42, 0x67, 0x51, 0x41, 0x53, 0x74, 0x53, 0x6d, 0x35,
    0x50, 0x4d, 0x37, 0x75, 0x62, 0x52, 0x4f, 0x69, 0x4b, 0x4b, 0x36, 0x2f,
    0x0a, 0x54, 0x32, 0x46, 0x6b, 0x4b, 0x6c, 0x68, 0x69, 0x54, 0x4f, 0x78,
    0x2b, 0x52, 0x79, 0x65, 0x6e, 0x6d, 0x33, 0x45, 0x69, 0x6f, 0x35, 0x39,
    0x65, 0x6d, 0x71, 0x2b, 0x6a, 0x58, 0x6c, 0x2b, 0x31, 0x6e, 0x68, 0x50,
    0x79, 0x53, 0x58, 0x35, 0x47, 0x32, 0x50, 0x51, 0x7a, 0x53, 0x52, 0x35,
    0x76, 0x64, 0x31, 0x64, 0x49, 0x68, 0x77, 0x67, 0x5a, 0x53, 0x52, 0x34,
    0x47, 0x79, 0x74, 0x74, 0x6b, 0x0a, 0x74, 0x52, 0x5a, 0x35, 0x37, 0x6b,
    0x2f, 0x4e, 0x49, 0x31, 0x62, 0x72, 0x55, 0x57, 0x38, 0x6a, 0x6f, 0x69,
    0x45, 0x4f, 0x4d, 0x4a, 0x41, 0x2f, 0x4d, 0x72, 0x37, 0x48, 0x37, 0x61,
    0x73, 0x78, 0x37, 0x77, 0x49, 0x52, 0x59, 0x44, 0x45, 0x39, 0x31, 0x46,
    0x73, 0x38, 0x47, 0x6b, 0x4b, 0x57, 0x64, 0x35, 0x4c, 0x68, 0x6f, 0x50,
    0x41, 0x51, 0x6a, 0x2b, 0x71, 0x64, 0x47, 0x33, 0x35, 0x43, 0x0a, 0x4f,
    0x4f, 0x2b, 0x73, 0x76, 0x64, 0x6b, 0x6d, 0x71, 0x48, 0x30, 0x4b, 0x5a,
    0x6f, 0x33, 0x32, 0x30, 0x5a, 0x55, 0x71, 0x64, 0x6c, 0x32, 0x6f, 0x6f,
    0x51, 0x3d, 0x3d, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x45, 0x4e, 0x44,
    0x20, 0x43, 0x45, 0x52, 0x54, 0x49, 0x46, 0x49, 0x43, 0x41, 0x54, 0x45,
    0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x00};

extern "C" const char test_signed_client_key[] = {
    0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e, 0x20, 0x50,
    0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b, 0x45, 0x59, 0x2d, 0x2d,
    0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49, 0x49, 0x43, 0x65, 0x51, 0x49, 0x42,
    0x41, 0x44, 0x41, 0x4e, 0x42, 0x67, 0x6b, 0x71, 0x68, 0x6b, 0x69, 0x47,
    0x39, 0x77, 0x30, 0x42, 0x41, 0x51, 0x45, 0x46, 0x41, 0x41, 0x53, 0x43,
    0x41, 0x6d, 0x4d, 0x77, 0x67, 0x67, 0x4a, 0x66, 0x41, 0x67, 0x45, 0x41,
    0x41, 0x6f, 0x47, 0x42, 0x41, 0x4f, 0x78, 0x55, 0x52, 0x39, 0x75, 0x68,
    0x76, 0x68, 0x62, 0x65, 0x56, 0x55, 0x49, 0x4d, 0x0a, 0x73, 0x35, 0x57,
    0x62, 0x48, 0x30, 0x70, 0x78, 0x30, 0x6d, 0x65, 0x68, 0x6c, 0x32, 0x2b,
    0x36, 0x73, 0x5a, 0x70, 0x4e, 0x6a, 0x7a, 0x76, 0x45, 0x32, 0x4b, 0x69,
    0x6d, 0x5a, 0x70, 0x48, 0x7a, 0x4d, 0x4a, 0x48, 0x75, 0x6b, 0x56, 0x48,
    0x30, 0x46, 0x66, 0x6b, 0x76, 0x68, 0x73, 0x30, 0x62, 0x38, 0x2b, 0x53,
    0x35, 0x55, 0x74, 0x39, 0x56, 0x4e, 0x55, 0x41, 0x71, 0x64, 0x33, 0x49,
    0x4d, 0x0a, 0x4a, 0x43, 0x43, 0x41, 0x45, 0x47, 0x74, 0x52, 0x4e, 0x6f,
    0x51, 0x68, 0x4d, 0x31, 0x74, 0x39, 0x59, 0x72, 0x32, 0x7a, 0x41, 0x63,
    0x6b, 0x53, 0x76, 0x62, 0x52, 0x61, 0x63, 0x70, 0x2b, 0x46, 0x4c, 0x2f,
    0x43, 0x6a, 0x39, 0x65, 0x44, 0x6d, 0x79, 0x6f, 0x30, 0x30, 0x4b, 0x73,
    0x56, 0x47, 0x61, 0x65, 0x65, 0x66, 0x41, 0x34, 0x44, 0x68, 0x34, 0x4f,
    0x57, 0x2b, 0x5a, 0x68, 0x6b, 0x54, 0x0a, 0x4e, 0x4b, 0x63, 0x6c, 0x64,
    0x58, 0x71, 0x6b, 0x53, 0x75, 0x6a, 0x31, 0x73, 0x45, 0x66, 0x32, 0x34,
    0x34, 0x4a, 0x5a, 0x59, 0x75, 0x71, 0x5a, 0x70, 0x36, 0x2f, 0x74, 0x41,
    0x67, 0x4d, 0x42, 0x41, 0x41, 0x45, 0x43, 0x67, 0x59, 0x45, 0x41, 0x69,
    0x32, 0x4e, 0x53, 0x56, 0x71, 0x70, 0x5a, 0x4d, 0x61, 0x66, 0x45, 0x35,
    0x59, 0x59, 0x55, 0x54, 0x63, 0x4d, 0x47, 0x65, 0x36, 0x51, 0x53, 0x0a,
    0x6b, 0x32, 0x6a, 0x74, 0x70, 0x73, 0x71, 0x59, 0x67, 0x67, 0x67, 0x49,
    0x32, 0x52, 0x6e, 0x4c, 0x4a, 0x2f, 0x32, 0x74, 0x4e, 0x5a, 0x77, 0x59,
    0x49, 0x35, 0x70, 0x77, 0x50, 0x38, 0x51, 0x56, 0x53, 0x62, 0x6e, 0x4d,
    0x61, 0x69, 0x46, 0x34, 0x67, 0x6f, 0x6b, 0x44, 0x35, 0x68, 0x47, 0x64,
    0x72, 0x4e, 0x44, 0x66, 0x54, 0x6e, 0x62, 0x32, 0x76, 0x2b, 0x79, 0x49,
    0x77, 0x59, 0x45, 0x48, 0x0a, 0x30, 0x77, 0x38, 0x2b, 0x6f, 0x47, 0x37,
    0x5a, 0x38, 0x31, 0x4b, 0x6f, 0x64, 0x73, 0x69, 0x5a, 0x53, 0x49, 0x44,
    0x4a, 0x66, 0x54, 0x47, 0x73, 0x41, 0x5a, 0x68, 0x56, 0x4e, 0x77, 0x4f,
    0x7a, 0x39, 0x79, 0x30, 0x56, 0x44, 0x38, 0x42, 0x42, 0x5a, 0x5a, 0x31,
    0x2f, 0x32, 0x37, 0x34, 0x5a, 0x68, 0x35, 0x32, 0x41, 0x55, 0x4b, 0x4c,
    0x6a, 0x5a, 0x53, 0x2f, 0x5a, 0x77, 0x49, 0x62, 0x53, 0x0a, 0x57, 0x32,
    0x79, 0x77, 0x79, 0x61, 0x38, 0x35, 0x35, 0x64, 0x50, 0x6e, 0x48, 0x2f,
    0x77, 0x6a, 0x2b, 0x30, 0x45, 0x43, 0x51, 0x51, 0x44, 0x39, 0x58, 0x38,
    0x44, 0x39, 0x32, 0x30, 0x6b, 0x42, 0x79, 0x54, 0x4e, 0x48, 0x68, 0x42,
    0x47, 0x31, 0x38, 0x62, 0x69, 0x41, 0x45, 0x5a, 0x34, 0x70, 0x78, 0x73,
    0x39, 0x66, 0x30, 0x4f, 0x41, 0x47, 0x38, 0x33, 0x33, 0x33, 0x65, 0x56,
    0x63, 0x49, 0x0a, 0x77, 0x32, 0x6c, 0x4a, 0x44, 0x4c, 0x73, 0x59, 0x44,
    0x5a, 0x72, 0x43, 0x42, 0x32, 0x6f, 0x63, 0x67, 0x41, 0x33, 0x6c, 0x55,
    0x64, 0x6f, 0x7a, 0x6c, 0x7a, 0x50, 0x43, 0x37, 0x59, 0x44, 0x59, 0x77,
    0x38, 0x72, 0x65, 0x67, 0x30, 0x74, 0x6b, 0x69, 0x52, 0x59, 0x35, 0x41,
    0x6b, 0x45, 0x41, 0x37, 0x73, 0x64, 0x4e, 0x7a, 0x4f, 0x65, 0x51, 0x73,
    0x51, 0x52, 0x6e, 0x37, 0x2b, 0x2b, 0x35, 0x0a, 0x30, 0x62, 0x50, 0x39,
    0x44, 0x74, 0x54, 0x2f, 0x69, 0x4f, 0x4e, 0x31, 0x67, 0x62, 0x66, 0x78,
    0x52, 0x7a, 0x43, 0x66, 0x43, 0x66, 0x58, 0x64, 0x6f, 0x4f, 0x74, 0x66,
    0x51, 0x57, 0x49, 0x7a, 0x54, 0x65, 0x50, 0x57, 0x74, 0x55, 0x52, 0x74,
    0x39, 0x58, 0x2f, 0x35, 0x44, 0x39, 0x4e, 0x6f, 0x66, 0x49, 0x30, 0x52,
    0x67, 0x35, 0x57, 0x32, 0x6f, 0x47, 0x79, 0x2f, 0x4d, 0x4c, 0x65, 0x35,
    0x0a, 0x2f, 0x73, 0x58, 0x48, 0x56, 0x51, 0x4a, 0x42, 0x41, 0x49, 0x75,
    0x70, 0x35, 0x58, 0x72, 0x4a, 0x44, 0x6b, 0x51, 0x79, 0x77, 0x4e, 0x5a,
    0x79, 0x41, 0x55, 0x55, 0x32, 0x65, 0x63, 0x6e, 0x32, 0x62, 0x43, 0x57,
    0x42, 0x46, 0x6a, 0x77, 0x74, 0x71, 0x64, 0x2b, 0x4c, 0x42, 0x6d, 0x75,
    0x4d, 0x63, 0x69, 0x49, 0x39, 0x66, 0x4f, 0x4b, 0x73, 0x5a, 0x74, 0x45,
    0x4b, 0x5a, 0x72, 0x7a, 0x2f, 0x0a, 0x55, 0x30, 0x6c, 0x6b, 0x65, 0x4d,
    0x52, 0x6f, 0x53, 0x77, 0x76, 0x58, 0x45, 0x38, 0x77, 0x6d, 0x47, 0x4c,
    0x6a, 0x6a, 0x72, 0x41, 0x62, 0x64, 0x66, 0x6f, 0x68, 0x72, 0x58, 0x46,
    0x6b, 0x43, 0x51, 0x51, 0x44, 0x5a, 0x45, 0x78, 0x2f, 0x4c, 0x74, 0x49,
    0x6c, 0x36, 0x4a, 0x49, 0x4e, 0x4a, 0x51, 0x69, 0x73, 0x77, 0x56, 0x65,
    0x30, 0x74, 0x57, 0x72, 0x36, 0x6b, 0x2b, 0x41, 0x53, 0x50, 0x0a, 0x31,
    0x57, 0x58, 0x6f, 0x54, 0x6d, 0x2b, 0x48, 0x59, 0x70, 0x6f, 0x46, 0x2f,
    0x58, 0x55, 0x76, 0x76, 0x39, 0x4c, 0x63, 0x63, 0x4e, 0x46, 0x31, 0x49,
    0x61, 0x7a, 0x46, 0x6a, 0x33, 0x34, 0x68, 0x77, 0x52, 0x51, 0x77, 0x68,
    0x78, 0x37, 0x77, 0x2f, 0x56, 0x35, 0x32, 0x49, 0x65, 0x62, 0x2b, 0x70,
    0x30, 0x6a, 0x55, 0x4d, 0x59, 0x47, 0x78, 0x41, 0x6b, 0x45, 0x41, 0x6a,
    0x44, 0x68, 0x64, 0x0a, 0x39, 0x70, 0x42, 0x4f, 0x31, 0x66, 0x4b, 0x58,
    0x57, 0x69, 0x58, 0x7a, 0x69, 0x39, 0x5a, 0x4b, 0x66, 0x6f, 0x79, 0x54,
    0x4e, 0x63, 0x55, 0x71, 0x33, 0x65, 0x42, 0x53, 0x56, 0x4b, 0x77, 0x50,
    0x47, 0x32, 0x6e, 0x49, 0x74, 0x67, 0x35, 0x79, 0x63, 0x58, 0x65, 0x6e,
    0x67, 0x6a, 0x54, 0x35, 0x73, 0x67, 0x63, 0x57, 0x44, 0x6e, 0x63, 0x69,
    0x49, 0x7a, 0x57, 0x37, 0x42, 0x49, 0x56, 0x49, 0x0a, 0x4a, 0x69, 0x71,
    0x4f, 0x73, 0x7a, 0x71, 0x39, 0x47, 0x57, 0x45, 0x53, 0x45, 0x72, 0x41,
    0x61, 0x74, 0x67, 0x3d, 0x3d, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x45,
    0x4e, 0x44, 0x20, 0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b,
    0x45, 0x59, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x00};

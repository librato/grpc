@rem Copyright 2017, Google Inc.
@rem All rights reserved.
@rem
@rem Redistribution and use in source and binary forms, with or without
@rem modification, are permitted provided that the following conditions are
@rem met:
@rem
@rem     * Redistributions of source code must retain the above copyright
@rem notice, this list of conditions and the following disclaimer.
@rem     * Redistributions in binary form must reproduce the above
@rem copyright notice, this list of conditions and the following disclaimer
@rem in the documentation and/or other materials provided with the
@rem distribution.
@rem     * Neither the name of Google Inc. nor the names of its
@rem contributors may be used to endorse or promote products derived from
@rem this software without specific prior written permission.
@rem
@rem THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
@rem "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
@rem LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
@rem A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
@rem OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
@rem SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
@rem LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
@rem DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
@rem THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
@rem (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
@rem OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

setlocal

@rem enter repo root
cd /d %~dp0\..\..\..

git submodule update --init

sh tools\run_tests\helper_scripts\run_tests_in_workspace.sh -t -j 4 -x c_windows_dbg_sponge_log.xml --report_suite_name c_windows_dbg -l c -c dbg
sh tools\run_tests\helper_scripts\run_tests_in_workspace.sh -t -j 4 -x c_windows_opt_sponge_log.xml --report_suite_name c_windows_opt -l c -c opt
sh tools\run_tests\helper_scripts\run_tests_in_workspace.sh -t -j 4 -x csharp_windows_dbg_sponge_log.xml --report_suite_name csharp_windows_dbg -l csharp -c dbg
sh tools\run_tests\helper_scripts\run_tests_in_workspace.sh -t -j 4 -x csharp_windows_opt_sponge_log.xml --report_suite_name csharp_windows_opt -l csharp -c opt
sh tools\run_tests\helper_scripts\run_tests_in_workspace.sh -t -j 4 -x node_windows_dbg_sponge_log.xml --report_suite_name node_windows_dbg -l node -c dbg
sh tools\run_tests\helper_scripts\run_tests_in_workspace.sh -t -j 4 -x node_windows_opt_sponge_log.xml --report_suite_name node_windows_opt -l node -c opt
sh tools\run_tests\helper_scripts\run_tests_in_workspace.sh -t -j 4 -x python_windows_dbg_sponge_log.xml --report_suite_name python_windows_dbg -l python -c dbg
sh tools\run_tests\helper_scripts\run_tests_in_workspace.sh -t -j 4 -x python_windows_opt_sponge_log.xml --report_suite_name python_windows_opt -l python -c opt

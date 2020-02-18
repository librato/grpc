# Install script for directory: ${CMAKE_INSTALL_SOLUTION_DIR}third_party/boringssl

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/grpc")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIGURATION)
  if(BUILD_CONFIGURATION)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIGURATION "${BUILD_CONFIGURATION}")
  else()
    set(CMAKE_INSTALL_CONFIGURATION "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIGURATION}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("${CMAKE_INSTALL_SOLUTION_DIR}/third_party/boringssl/crypto/cmake_install.cmake")
  include("${CMAKE_INSTALL_SOLUTION_DIR}/third_party/boringssl/third_party/fiat/cmake_install.cmake")
  include("${CMAKE_INSTALL_SOLUTION_DIR}/third_party/boringssl/ssl/cmake_install.cmake")
  include("${CMAKE_INSTALL_SOLUTION_DIR}/third_party/boringssl/ssl/test/cmake_install.cmake")
  include("${CMAKE_INSTALL_SOLUTION_DIR}/third_party/boringssl/fipstools/cmake_install.cmake")
  include("${CMAKE_INSTALL_SOLUTION_DIR}/third_party/boringssl/tool/cmake_install.cmake")
  include("${CMAKE_INSTALL_SOLUTION_DIR}/third_party/boringssl/decrepit/cmake_install.cmake")

endif()


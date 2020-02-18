# Install script for directory: ${CMAKE_INSTALL_SOLUTION_DIR}third_party/cares/cares

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/cares.lib")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/cares.lib")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/cares.lib")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/cares.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "${CMAKE_INSTALL_SOLUTION_DIR}../third_party/cares/cares/ares.h"
    "${CMAKE_INSTALL_SOLUTION_DIR}../third_party/cares/cares/ares_version.h"
    "${CMAKE_INSTALL_SOLUTION_DIR}../third_party/cares/cares/ares_dns.h"
    "${CMAKE_INSTALL_SOLUTION_DIR}third_party/cares/cares/ares_build.h"
    "${CMAKE_INSTALL_SOLUTION_DIR}../third_party/cares/cares/ares_rules.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares/c-ares-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares/c-ares-targets.cmake"
         "${CMAKE_INSTALL_SOLUTION_DIR}/third_party/cares/cares/CMakeFiles/Export/lib/cmake/c-ares/c-ares-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares/c-ares-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares/c-ares-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares" TYPE FILE FILES "${CMAKE_INSTALL_SOLUTION_DIR}/third_party/cares/cares/CMakeFiles/Export/lib/cmake/c-ares/c-ares-targets.cmake")
  if("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares" TYPE FILE FILES "${CMAKE_INSTALL_SOLUTION_DIR}/third_party/cares/cares/CMakeFiles/Export/lib/cmake/c-ares/c-ares-targets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares" TYPE FILE FILES "${CMAKE_INSTALL_SOLUTION_DIR}/third_party/cares/cares/CMakeFiles/Export/lib/cmake/c-ares/c-ares-targets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares" TYPE FILE FILES "${CMAKE_INSTALL_SOLUTION_DIR}/third_party/cares/cares/CMakeFiles/Export/lib/cmake/c-ares/c-ares-targets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares" TYPE FILE FILES "${CMAKE_INSTALL_SOLUTION_DIR}/third_party/cares/cares/CMakeFiles/Export/lib/cmake/c-ares/c-ares-targets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares" TYPE FILE FILES "${CMAKE_INSTALL_SOLUTION_DIR}/third_party/cares/cares/c-ares-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "${CMAKE_INSTALL_SOLUTION_DIR}/third_party/cares/cares/libcares.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/ahost.exe")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/ahost.exe")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/ahost.exe")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/ahost.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/adig.exe")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/adig.exe")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/adig.exe")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/adig.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/acountry.exe")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/acountry.exe")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/acountry.exe")
  elseif("${CMAKE_INSTALL_CONFIGURATION}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "${CMAKE_INSTALL_THIRD_PARTY_DIR}/acountry.exe")
  endif()
endif()


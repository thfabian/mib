################################################################################
#  mib - Micro Benchmark
#
#  Copyright (C) 2016  Fabian Thuring (thfabian@student.ethz.ch)
#
#  This file is distributed under the MIT Open Source License. See
#  LICENSE.TXT for details.
#
################################################################################
cmake_minimum_required(VERSION 2.8)
project(mib)

if(NOT(CMAKE_MAJOR_VERSION LESS 3) AND NOT(CMAKE_MINOR_VERSION LESS 2))
    cmake_policy(SET CMP0054 OLD)
endif()

option(MIB_TEST "Build unit tests" OFF)

################################################################################
# Compiler Flags
################################################################################
if(NOT(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -Wall")
else()
    # We will link statically against the C++ runtime libraries on Windows. 
    set(CompilerFlags
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        string(REPLACE "/MDd" "/MTd" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif()

################################################################################
# CMake options
################################################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: Debug Release" FORCE)
    message(STATUS "Setting build type to 'Release' as none was specified.")
endif(NOT CMAKE_BUILD_TYPE)
                     
################################################################################
# Compilation (only needed for tests)
################################################################################

# External includes
include_directories(${PROJECT_SOURCE_DIR}/external)

# Micro Benchmark     
include_directories(${PROJECT_SOURCE_DIR}/include)
set(MIB_HEADER "${PROJECT_SOURCE_DIR}/include/mib.h")

if(MIB_TEST)
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif(MIB_TEST)

################################################################################
# Installation
################################################################################
install(FILES ${MIB_HEADER} DESTINATION include)

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

file(GLOB MIB_TEST_SOURCES "mib_test_*.cpp")
set(MIB_TEST_HEADERS mib_test.h)

add_executable(mib_test ${MIB_TEST_SOURCES} 
                        ${MIB_TEST_HEADERS}
                        ${MIB_HEADER})
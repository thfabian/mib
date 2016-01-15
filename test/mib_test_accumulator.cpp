/**
 *  mib - Micro Benchmark
 *
 *  Copyright (C) 2016  Fabian Thuring (thfabian@student.ethz.ch)
 *
 *  This file is distributed under the MIT Open Source License. See
 *  LICENSE.TXT for details.
 */

#include "mib_test.h"
#include <mib.h>

MIB_INTERNAL_NAMESPACE_BEGIN

#define EPSILON 1e-5

TEST_CASE("Accumulator ", "[Accumulator]")
{
    Accumulator acc;
    acc << 600;
    acc << 470;
    acc << 170;
    acc << 430;
    acc << 300;
    CHECK(acc.sum() == 1970.0);
    CHECK(acc.count() == 5);
    CHECK(acc.mean() == 394.0);
    CHECK(std::abs(acc.dev() - 164.711869) < EPSILON);
    CHECK(std::abs(acc.std() - 73.661387) < EPSILON);
}

MIB_INTERNAL_NAMESPACE_END
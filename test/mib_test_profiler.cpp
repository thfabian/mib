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
#include <numeric>
#include <list>
#include <vector>

TEST_CASE("Profiler", "[Profiler]")
{
    std::vector<int> vec(1000);
    std::list<int> list(1000);

    SECTION("Tree print I")
    {
        for(int i = 0; i < 1; ++i)
        {
            MIB_START("test1");

            MIB_START("leaf1");
            std::iota(vec.begin(), vec.end(), 0);
            MIB_STOP("leaf1");

            MIB_START("leaf2");
            std::iota(vec.begin(), vec.end(), 0);
            MIB_STOP("leaf2");

            MIB_START("leaf3");
            std::iota(vec.begin(), vec.end(), 0);
            MIB_STOP("leaf3");

            MIB_STOP("test1");
        }
        MIB_PRINT("cycle")
    }

    SECTION("Tree print II")
    {
        for(int i = 0; i < 1213; ++i)
        {
            MIB_START("vector");

            MIB_START("std::iota<vector>");
            std::iota(vec.begin(), vec.end(), 0);
            MIB_STOP("std::iota<vector>");

            MIB_START("std::sort<vector>");
            std::sort(vec.begin(), vec.end());
            MIB_STOP("std::sort<vector>");

            MIB_NEXT("list");

            MIB_START("std::iota<list>");
            std::iota(list.begin(), list.end(), 0);
            MIB_STOP("std::iota<list>");

            MIB_START("std::sort<list>");
            list.sort();
            MIB_STOP("std::sort<list>");

            MIB_STOP("list");
        }
        MIB_PRINT("cycle")
    }

#ifndef MIB_NO_UTF8    
    SECTION("Start/end tag")
    {
        MIB_START("vector_2");
        REQUIRE_THROWS(MIB_STOP("vecto_2"));
    }
#endif
    
}

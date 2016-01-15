## mib - Micro Benchmark (0.0.1)

### DESCRIPTION

A header-only, cross-platform, lightweight C++11 micro-benchmark library which provides drop-in support for timing code within a precision of a a few cycles.

### BUILD

The library consists of a single header file [mib.h](https://github.com/thfabian/mib/blob/master/include/mib.h). The library only depends on the C++ STL and certain platform specific headers, most notably `windows.h` and `unistd.h`.

### USAGE

##### Instructions

The library uses the [rdtsc](https://en.wikipedia.org/wiki/Time_Stamp_Counter) timer for accurate measurement. The entire functionality is encapsulated in a few macros.

* `MIB_START(name)`: Register an event, identified by `name` (given as a *string*, hence "."), and start the timer. If this is called within an already existing event, the event will be trated as a child node of the parent event.
* `MIB_STOP(name)`: Stop the event and timer given by `name`.
* `MIB_NEXT(name)`: Stop the **last** event and timer and register a new event `name`.
* `MIB_PRINT(mod)`: Prints *all* events in a tree like fashion to the console. The argument `mod` can be either `cycle` (using rdtsc timer) or `nsec` (using STL chrono) depending on the preferred time-unit.
 

The identifier `name` has to be unique as starting and stopping an event multiple times given by the same name will be treated as the same event (See example).

The library can be configured with `#define` the following macros before including `mib.h`

* `MIB_NO_COLOR`: Don't color terminal output.
* `MIB_NO_UTF8`: Don't use special utf8 characters to draw the tree (default on Windows).
* `MIB_NO_EXCEPTION`: Don't throw exceptions, abort instead.

##### Example

The following simple example shows how to measure the [std::sort](http://en.cppreference.com/w/cpp/algorithm/random_shuffle) operation on a vector and a list. 

```c++
#include "mib.h"
#include <algorithm>  // std::sort, std::generate
#include <vector>     // std::vector
#include <list>       // std::list
#include <random>     // std::mt19937

int main()
{
    std::vector<int> vec(1000);
    std::list<int> list(1000);

    // Fill containers with random numbers
    std::random_device rnd_device;
    std::mt19937 mersenne_engine(rnd_device());
    std::generate(vec.begin(), vec.end(), mersenne_engine);
    std::generate(list.begin(), list.end(), mersenne_engine);

    // Profiler sorting over 1000 repetitions
    for(int i=0; i < 1000; ++i)
    {
        MIB_START("vector sort")
        std::sort(vec.begin(), vec.end());
        MIB_NEXT("list sort")
        list.sort();
        MIB_STOP("list sort")
    }

    MIB_PRINT("cycle")
    return 0;
}

```

this will result in something like:

```
================================================================================
┬ (% of parent) name                           cycle_mean   spread    run_cnt
├─  8% vector sort                            [      3495       3%       1000 ]
└─ 92% list sort                              [     38298       3%       1000 ]

```

### LICENSE

#####  The MIT License (MIT)
Copyright (c) 2016 Fabian Thuring

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
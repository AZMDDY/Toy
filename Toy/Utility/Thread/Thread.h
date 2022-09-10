// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_THREAD_H
#define TOY_THREAD_H
#include <chrono>
#include <thread>
namespace Utility {
using HighClock = std::chrono::high_resolution_clock;

// 高精度sleep
static void SleepFor(double ms)
{
    static constexpr std::chrono::duration<double, std::milli> MinSleepDuration(0);
    HighClock::time_point start = HighClock::now();
    while (std::chrono::duration<double, std::milli>(HighClock::now() - start).count() < ms) {
        std::this_thread::sleep_for(MinSleepDuration);
    }
}
}  // namespace Utility
#endif  // TOY_THREAD_H

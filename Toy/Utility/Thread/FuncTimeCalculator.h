// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_FUNCTIMECALCULATOR_H
#define TOY_FUNCTIMECALCULATOR_H
#include <chrono>
#include <string>
#include "Log.h"

#define FUNC_TIME_CAL() Utility::FuncTimeCalculator ftc(__FUNCTION__)

namespace Utility {
struct FuncTimeCalculator {
public:
    FuncTimeCalculator(const std::string& func) : funcName(func) { start = std::chrono::high_resolution_clock::now(); }
    ~FuncTimeCalculator()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        LOG_ERROR() << "the function[" << funcName << "] takes " << elapsed.count() << "ms";
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::string funcName;
};
}  // namespace Utility
#endif  // TOY_FUNCTIMECALCULATOR_H

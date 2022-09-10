// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 日志输出接口

#include "Log.h"
#include <iostream>

namespace Utility {
LogLevel g_logLevel = LogLevel::ERROR;

void SetLogLevel(LogLevel logLevel)
{
    g_logLevel = logLevel;
}
namespace Details {
    LogStream::LogStream(LogLevel logLevel) : logLevel(logLevel) {}

    LogStream::~LogStream()
    {
        if (logLevel >= g_logLevel) {
            std::cerr << data << std::endl << std::flush;
        }
    }

    LogStream& LogStream::operator<<(const std::string& value)
    {
        data += value;
        return *this;
    }

    LogStream& LogStream::operator<<(const char* value)
    {
        data += value;
        return *this;
    }

    LogStream& LogStream::operator<<(char* value)
    {
        data += value;
        return *this;
    }
}  // namespace Details
}  // namespace Utility
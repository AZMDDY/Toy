// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 日志输出接口

#ifndef TOY_LOG_H
#define TOY_LOG_H
#include <string>
#include <type_traits>

#define FILENAME_ (std::strrchr(__FILE__, '/') ? (std::strrchr(__FILE__, '/') + 1) : __FILE__)

#define LOG_DEBUG()                              \
    Utility::Details::LogStream(LogLevel::DEBUG) \
        << "[D: " << __TIME__ << " <" << __FUNCTION__ << "> " << FILENAME_ << ":" << __LINE__ << "] "
#define LOG_INFO()                              \
    Utility::Details::LogStream(LogLevel::INFO) \
        << "[I: " << __TIME__ << " <" << __FUNCTION__ << "> " << FILENAME_ << ":" << __LINE__ << "] "
#define LOG_ERROR()                              \
    Utility::Details::LogStream(LogLevel::ERROR) \
        << "[E: " << __TIME__ << " <" << __FUNCTION__ << "> " << FILENAME_ << ":" << __LINE__ << "] "

enum class LogLevel { DEBUG = 0, INFO = 1, ERROR = 2 };

namespace Utility {
// 设置全局的日志打印级别
void SetLogLevel(LogLevel logLevel);

namespace Details {
    class LogStream {
    public:
        explicit LogStream(LogLevel logLevel);
        LogStream(LogStream&) = delete;
        LogStream(LogStream&&) = delete;
        LogStream& operator=(const LogStream&) = delete;
        LogStream& operator=(LogStream&&) = delete;
        ~LogStream();

        template<class T>
        LogStream& operator<<(T value)
        {
            data += std::to_string(this->template Convert<T>(value));
            return *this;
        }

        LogStream& operator<<(const std::string& value);
        LogStream& operator<<(const char* value);
        LogStream& operator<<(char* value);

    private:
        template<class T>
        typename std::enable_if<std::is_enum<T>::value && std::is_integral<std::underlying_type_t<T>>::value,
                                size_t>::type
        Convert(T value)
        {
            return static_cast<size_t>(value);
        }

        template<class T>
        typename std::enable_if<!std::is_enum<T>::value, T>::type Convert(T value)
        {
            return value;
        }

    private:
        std::string data;
        LogLevel logLevel;
    };
}  // namespace Details
}  // namespace Utility
#endif  // TOY_LOG_H

/**
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#pragma once

#include <cstdarg>
#include <cstdio>

enum class LogLevel
{
    INFO,
    WARN,
    ERROR,
    FATAL
};

inline void log(const LogLevel& level, const char* str, ...)
{
    std::FILE* log_file = stderr;
    std::va_list va_args;

    switch(level)
    {
    case LogLevel::INFO:
        fputs("[info] ", log_file);
        break;
    case LogLevel::WARN:
        fputs("[warn] ", log_file);
        break;
    case LogLevel::ERROR:
        fputs("[error] ", log_file);
        break;
    case LogLevel::FATAL:
        fputs("[fatal] ", log_file);
        break;
    default:
        fputs("[info] ", log_file);
        break;
    }

    va_start(va_args, str);
    vfprintf(log_file, str, va_args);
    va_end(va_args);
}

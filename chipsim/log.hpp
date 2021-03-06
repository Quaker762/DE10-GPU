/**
 * This file is part of Rush3D.
 * Copyright (c) 2020 Jack Allan, Matthew Atkin and Jesse Buhagiar
 *
 * Rush3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Rush3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Rush3D.  If not, see <https://www.gnu.org/licenses/>.
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
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
 * Date: 27/9/2020
 */
#include "tga.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

void tga_write_file(std::vector<uint32_t>& data)
{
    TGAHeader header;
    std::time_t time = std::time(nullptr);
    std::string timestr = "/fs/screenshot_" + std::to_string(time) + ".tga";

    std::printf("%s\n", timestr.c_str());

    std::ofstream file(timestr, std::ios::out | std::ios::binary);
    if(!file)
    {
        fputs("tga_write_file: failed to open a handle to image file!\n", stderr);
        abort();
    }

    header.width = 640;
    header.height = 480;

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size() * 4));
    file.close();
}

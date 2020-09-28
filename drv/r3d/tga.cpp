/**
 *
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 27/9/2020
 */
#include "tga.h"

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
    file.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
    file.close();
}

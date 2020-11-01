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
 * TGA structures and function definitions
 *
 * Author: Jesse Buhagiar
 * Date: 27/9/2020
 */
#pragma once
#include <cstdint>
#include <vector>

static constexpr uint8_t TYPE_RGB24 = 2;
static constexpr uint8_t FLAGS_FLIP = 0x20;

#pragma pack(push, 1)
struct TGAHeader
{
    uint8_t id_size = 0;       /**< Size of the ID field that follows this header (usually 0) */
    uint8_t colormap = 0;      /**< Is this image paletted (THIS MUST ALWAYS BE 0 FOR US!) */
    uint8_t type = TYPE_RGB24; /**< Type of image (ALWAYS 2 FOR RGB24!) */
    uint8_t unused[5] = {};
    uint16_t x_origin = 0; /**< Co-ordinate for first X value */
    uint16_t y_origin = 0; /**< Co-ordinate for first Y value */
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t bpp = 32; /**< Bits per pixel */
    uint8_t flags = FLAGS_FLIP;
};
#pragma pack(pop)

void tga_write_file(std::vector<uint32_t>& data);
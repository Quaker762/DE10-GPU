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

#include "../constants.h"

#include <SDL2/SDL.h>
#include <cstdint>
#include <queue>

#define FRAMEBUFFER_MEMORY_SIZE 2 * MB
#define DEFAULT_WIDTH           800
#define DEFAULT_HEIGHT          600

struct FrameBufferWindow
{
    int width;
    int height;
};

enum Commands
{
    COMMAND_CLEAR,
};

enum RegisterOffsets
{
    STATUS = 0,
    fbCOLOR,
    fbFILL,
    fbWIDTH,
    fbHEIGHT,
    vertexAx,
    vertexAy,
    vertexBx,
    vertexBy,
    vertexCx,
    vertexCy,
    triStartR,
    triStartG,
    triStartB,
    triStartA,
    triRdX,
    triGdX,
    triBdX,
    triAdX,
    triRdY,
    triGdY,
    triBdY,
    triAdY,

    cmdTriangle,
};

namespace Chip
{
/**
 * Framebuffer interface (AKA Pixel Control Unit [PCU])
 *
 * This is effectively the "core" graphics chip. It's job is to manage
 * blitting everything to the framebuffer. It also contains the register
 * file for the entire GPU as well as
 *
 * We have 2MiB of framebuffer, which supports a resolution up to 800x600x24.
 * At the moment, we only support 24 bit color (no alpha channel)
 *
 * Very similar to the SST-1. Verbal information on how this system worked can be
 * found here: https://youtu.be/3MghYhf-GhU?t=3264
 */
class PCU
{
public:
    PCU() = delete;
    PCU(const SDL_Surface*);

    void handle_command(uint8_t cmd);
    void set_window_size(int, int);

    void push_fifo(uint32_t);
    void write_register(RegisterOffsets offset, uint32_t value);
    uint32_t read_register(RegisterOffsets offset);

    void swap_buffers();

private:
    void put_pixel(int, int, uint32_t pixel);
    void draw_wireframe_triangle();
    void draw_filled_triangle();
    void draw_line_debug(int startX, int startY, int endX, int endY, uint32_t);
    void draw_line(int startX, int startY, int endX, int endY);
    void fill_framebuffer();

    void draw_flat_top(float x1, float y1, float x2, float y2, float x3, float y3);
    void draw_flat_bottom(float x1, float y1, float x2, float y2, float x3, float y3);

private:
    uint32_t* m_framebuffer;
    uint32_t* m_backbuffer;

    FrameBufferWindow m_window_size{ 800, 600 };

    std::queue<uint32_t> m_fifo;

    uint32_t m_registers[256]; // 256 Registers
};

} // namespace Chip
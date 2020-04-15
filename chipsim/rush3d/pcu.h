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
    void draw_line(int startX, int startY, int endX, int endY);
    void fill_framebuffer();

private:
    uint32_t* m_framebuffer;
    uint32_t* m_backbuffer;

    FrameBufferWindow m_window_size{ 800, 600 };

    std::queue<uint32_t> m_fifo;

    uint32_t m_registers[256]; // 256 Registers
};

} // namespace Chip
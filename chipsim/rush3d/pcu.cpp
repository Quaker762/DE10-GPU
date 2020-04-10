/**
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#include "pcu.h"

#include <cassert>
#include <cstdio>
#include <cstring>

//#define DEBUG_PCU

using namespace Chip;

PCU::PCU(const SDL_Surface* screen)
{
    if(screen == nullptr)
    {
        printf("pcu: failed to get hwnd surface! Reason: %s\n", SDL_GetError());
        exit(-1);
    }

    m_framebuffer = reinterpret_cast<uint32_t*>(screen->pixels);
    m_backbuffer = new uint32_t[FRAMEBUFFER_MEMORY_SIZE / sizeof(uint32_t)];

#ifdef DEBUG_PCU
    printf("pcu: initialized PCU with %d memory\n", FRAMEBUFFER_MEMORY_SIZE);
    printf("pcu: 0x%ld\n", sizeof(m_backbuffer));
#endif
}

void PCU::set_window_size(int width, int height)
{
    m_window_size.width = width;
    m_window_size.height = height;
}

void PCU::push_fifo(uint32_t command)
{
    m_fifo.push(command);
}

void PCU::put_pixel(int x, int y, uint32_t pixel)
{
#ifdef DEBUG_PCU
    // printf("pcu: writing pixel 0x%x to (%d, %d)\n", pixel, x, y);
#endif
    pixel &= 0x00ffffff;
    m_backbuffer[x + y * m_window_size.width] = pixel;
}

void PCU::fill_framebuffer()
{
    uint32_t pixel = m_registers[RegisterOffsets::fbCOLOR] & 0x00ffffff;
    for(int y = 0; y < m_window_size.height; y++)
    {
        for(int x = 0; x < m_window_size.width; x++)
        {
            put_pixel(x, y, pixel);
        }
    }
}

void PCU::write_register(RegisterOffsets offset, uint32_t value)
{
    if(offset == RegisterOffsets::fbFILL)
    {
        fill_framebuffer();
        return;
    }

    m_registers[offset] = value;
}

uint32_t PCU::read_register(RegisterOffsets offset)
{
    return m_registers[offset];
}

void PCU::swap_buffers()
{
    memcpy(m_framebuffer, m_backbuffer, FRAMEBUFFER_MEMORY_SIZE);
}
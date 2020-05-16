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
    int location = x + y * m_window_size.width;

    m_backbuffer[location] = pixel;
}

// Extremely Fast Line Algorithm Var B (Multiplication)
// Copyright 2001-2, By Po-Han Lin

// Freely useable in non-commercial applications as long as credits
// to Po-Han Lin and link to http://www.edepot.com is provided in source
// code and can been seen in compiled executable.  Commercial
// applications please inquire about licensing the algorithms.
//
// Lastest version at http://www.edepot.com/phl.html
void PCU::draw_line(int startX, int startY, int endX, int endY, uint32_t color)
{
    bool yLonger = false;
    int incrementVal;
    int shortLen = endY - startY;
    int longLen = endX - startX;

    if(abs(shortLen) > abs(longLen))
    {
        int swap = shortLen;
        shortLen = longLen;
        longLen = swap;
        yLonger = true;
    }

    if(longLen < 0)
        incrementVal = -1;
    else
        incrementVal = 1;

    double multDiff;
    if(longLen == 0.0)
        multDiff = static_cast<double>(shortLen);
    else
        multDiff = static_cast<double>(shortLen) / static_cast<double>(longLen);
    if(yLonger)
    {
        for(int i = 0; i != longLen; i += incrementVal)
        {
            // draw(surface, x + (int)((double)i * multDiff), y + i);
            put_pixel(startX + static_cast<int>(static_cast<double>(i * multDiff)), startY + i, color);
        }
    }
    else
    {
        for(int i = 0; i != longLen; i += incrementVal)
        {
            // myPixel(surface, x + i, y + (int)((double)i * multDiff));
            put_pixel(startX + i, startY + static_cast<int>((static_cast<double>(i) * multDiff)), color);
        }
    }
}

void PCU::draw_wireframe_triangle()
{
    // We draw lines between vertex A and B, vertex A and C and vertex B and C
    uint32_t a_x = read_register(RegisterOffsets::vertexAx);
    uint32_t a_y = read_register(RegisterOffsets::vertexAy);
    uint32_t b_x = read_register(RegisterOffsets::vertexBx);
    uint32_t b_y = read_register(RegisterOffsets::vertexBy);
    uint32_t c_x = read_register(RegisterOffsets::vertexCx);
    uint32_t c_y = read_register(RegisterOffsets::vertexCy);

    draw_line(a_x, a_y, b_x, b_y, 0x00ff0000);
    draw_line(a_x, a_y, c_x, c_y, 0x00ff0000);
    draw_line(b_x, b_y, c_x, c_y, 0x00ff0000);
}

void PCU::draw_flat_bottom(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float dxdy1 = (static_cast<float>(x2) - static_cast<float>(x1)) / (static_cast<float>(y2) - static_cast<float>(y1));
    float dxdy2 = (static_cast<float>(x3) - static_cast<float>(x1)) / (static_cast<float>(y3) - static_cast<float>(y1));
    float left_x = x1;
    float right_x = left_x;

    for(uint32_t y = y1; y <= y2; y++)
    {
        draw_line(static_cast<int>(left_x), y, static_cast<int>(right_x), y, 0xffffffff);

        left_x += dxdy1;
        right_x += dxdy2;
    }
}

void PCU::draw_flat_top(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float dxdy1 = (static_cast<float>(x3) - static_cast<float>(x1)) / (static_cast<float>(y3) - static_cast<float>(y1));
    float dxdy2 = (static_cast<float>(x3) - static_cast<float>(x2)) / (static_cast<float>(y3) - static_cast<float>(y2));
    float left_x = x3;
    float right_x = left_x;

    for(uint32_t y = y3; y > y1; y--)
    {
        draw_line(static_cast<int>(left_x), y, static_cast<int>(right_x), y, 0xffffffff);

        left_x -= dxdy1;
        right_x -= dxdy2;
    }
}

// Holy shit this page is a treasure trove
// http://www-users.mat.uni.torun.pl/~wrona/3d_tutor/tri_fillers.html
// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
void PCU::draw_filled_triangle()
{
    // Tells us whether or not this triangle is left-handed (point facing the left)
    // or right-handed (point facing the right)
    bool left_handed = read_register(RegisterOffsets::cmdTriangle) >> 31;
    uint32_t a_x = read_register(RegisterOffsets::vertexAx);
    uint32_t a_y = read_register(RegisterOffsets::vertexAy);
    uint32_t b_x = read_register(RegisterOffsets::vertexBx);
    uint32_t b_y = read_register(RegisterOffsets::vertexBy);
    uint32_t c_x = read_register(RegisterOffsets::vertexCx);
    uint32_t c_y = read_register(RegisterOffsets::vertexCy);

    if(b_y == c_y) // Flat bottom triangle
    {
        draw_flat_bottom(a_x, a_y, b_x, b_y, c_x, c_y);
    }
    else if(a_y == b_y) // Flat top triangle
    {
        draw_flat_top(a_x, a_y, b_x, b_y, c_x, c_y);
    }
    else
    {
        // We need to draw one bottom flat triangle and one top flat triangle
        // We know where the elbow's x and y coordinates are (Vertex B)
        float d_x = (static_cast<float>(a_x) + (static_cast<float>(b_y - a_y) / static_cast<float>(c_y - a_y)) * (static_cast<float>(c_x) - static_cast<float>(a_x)));
        draw_flat_bottom(a_x, a_y, b_x, b_y, d_x, b_y);
        draw_flat_top(b_x, b_y, d_x, b_y, c_x, c_y);
    }
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
    else if(offset == RegisterOffsets::cmdTriangle)
    {
        // draw_wireframe_triangle();
        draw_filled_triangle();
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
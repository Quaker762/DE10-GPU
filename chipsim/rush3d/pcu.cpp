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
#include "pcu.h"

#include <algorithm>
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
void PCU::draw_line_debug(int startX, int startY, int endX, int endY, uint32_t color)
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

void PCU::draw_line(int startX, int startY, int endX, int endY)
{
    bool yLonger = false;
    int incrementVal;
    int shortLen = endY - startY;
    int longLen = endX - startX;

    // Color stuff
    float dxR = static_cast<float>(read_register(RegisterOffsets::triRdX));
    float dxG = static_cast<float>(read_register(RegisterOffsets::triGdX));
    float dxB = static_cast<float>(read_register(RegisterOffsets::triBdX));
    float dyR = static_cast<float>(read_register(RegisterOffsets::triRdY));
    float dyG = static_cast<float>(read_register(RegisterOffsets::triGdY));
    float dyB = static_cast<float>(read_register(RegisterOffsets::triBdY));

    int currX = startX;
    int currY = startY;

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

    uint32_t combine_color;
    if(yLonger)
    {
        for(int i = 0; i != longLen; i += incrementVal)
        {
            // Hahaha, ripping off 3Dfx yet again!
            // If the pixel moves to the right, increment startX by dxX, if it
            // moves to the left, then decrement it. Same goes for
            // y values
            float startR = static_cast<float>(read_register(RegisterOffsets::triStartR));
            float startG = static_cast<float>(read_register(RegisterOffsets::triStartG));
            float startB = static_cast<float>(read_register(RegisterOffsets::triStartB));

            combine_color = (static_cast<uint8_t>(startR) << 16) | (static_cast<uint8_t>(startG) << 8) | (static_cast<uint8_t>(startB));
            put_pixel(startX + static_cast<int>(static_cast<double>(i * multDiff)), startY + i, combine_color);

            // X
            if((startX + static_cast<int>(static_cast<double>(i * multDiff))) > currX)
            {
                startR = std::clamp(startR + dxR, 0.0f, 255.0f);
                startG = std::clamp(startG + dxG, 0.0f, 255.0f);
                startB = std::clamp(startB + dxB, 0.0f, 255.0f);
            }
            else if((startX + static_cast<int>(static_cast<double>(i * multDiff))) < currX)
            {
                startR = std::clamp(startR - dxR, 0.0f, 255.0f);
                startG = std::clamp(startG - dxG, 0.0f, 255.0f);
                startB = std::clamp(startB - dxB, 0.0f, 255.0f);
            }

            // Same for Y
            if((startY + i) > currY)
            {
                startR = std::clamp(startR + dyR, 0.0f, 255.0f);
                startG = std::clamp(startG + dyG, 0.0f, 255.0f);
                startB = std::clamp(startB + dyB, 0.0f, 255.0f);
            }
            else if((startY + i) < currY)
            {
                startR = std::clamp(startR - dyR, 0.0f, 255.0f);
                startG = std::clamp(startG - dyG, 0.0f, 255.0f);
                startB = std::clamp(startB - dyB, 0.0f, 255.0f);
            }

            // Write the registers back
            write_register(RegisterOffsets::triStartR, static_cast<uint32_t>(startR));
            write_register(RegisterOffsets::triStartG, static_cast<uint32_t>(startG));
            write_register(RegisterOffsets::triStartB, static_cast<uint32_t>(startB));

            currX = startX + static_cast<int>(static_cast<double>(i * multDiff));
            currY = startY + i;
        }
    }
    else
    {
        for(int i = 0; i != longLen; i += incrementVal)
        {
            float startR = static_cast<float>(read_register(RegisterOffsets::triStartR));
            float startG = static_cast<float>(read_register(RegisterOffsets::triStartG));
            float startB = static_cast<float>(read_register(RegisterOffsets::triStartB));

            combine_color = (static_cast<uint8_t>(startR) << 16) | (static_cast<uint8_t>(startG) << 8) | (static_cast<uint8_t>(startB));
            put_pixel(startX + i, startY + static_cast<int>((static_cast<double>(i) * multDiff)), combine_color);

            // X
            if((startX + i) > currX)
            {
                startR = std::clamp(startR + dxR, 0.0f, 255.0f);
                startG = std::clamp(startG + dxG, 0.0f, 255.0f);
                startB = std::clamp(startB + dxB, 0.0f, 255.0f);
            }
            else if((startX + i) < currX)
            {
                startR = std::clamp(startR - dxR, 0.0f, 255.0f);
                startG = std::clamp(startG - dxG, 0.0f, 255.0f);
                startB = std::clamp(startB - dxB, 0.0f, 255.0f);
            }

            // Same for Y
            if((startY + static_cast<int>((static_cast<double>(i) * multDiff))) > currY)
            {
                startR = std::clamp(startR + dyR, 0.0f, 255.0f);
                startG = std::clamp(startG + dyG, 0.0f, 255.0f);
                startB = std::clamp(startB + dyB, 0.0f, 255.0f);
            }
            else if((startY + static_cast<int>((static_cast<double>(i) * multDiff))) < currY)
            {
                startR = std::clamp(startR - dyR, 0.0f, 255.0f);
                startG = std::clamp(startG - dyG, 0.0f, 255.0f);
                startB = std::clamp(startB - dyB, 0.0f, 255.0f);
            }

            // Write the registers back
            write_register(RegisterOffsets::triStartR, static_cast<uint32_t>(startR));
            write_register(RegisterOffsets::triStartG, static_cast<uint32_t>(startG));
            write_register(RegisterOffsets::triStartB, static_cast<uint32_t>(startB));

            currX = startX + i;
            currY = startY + static_cast<int>((static_cast<double>(i) * multDiff));
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

    draw_line(a_x, a_y, b_x, b_y);
    draw_line(a_x, a_y, c_x, c_y);
    draw_line(b_x, b_y, c_x, c_y);
}

void PCU::draw_flat_bottom(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float dxdy1 = (static_cast<float>(x2) - static_cast<float>(x1)) / (static_cast<float>(y2) - static_cast<float>(y1));
    float dxdy2 = (static_cast<float>(x3) - static_cast<float>(x1)) / (static_cast<float>(y3) - static_cast<float>(y1));
    float left_x = x1;
    float right_x = left_x;

    float startR = static_cast<float>(read_register(RegisterOffsets::triStartR));
    float startG = static_cast<float>(read_register(RegisterOffsets::triStartG));
    float startB = static_cast<float>(read_register(RegisterOffsets::triStartB));
    float dyR = static_cast<float>(read_register(RegisterOffsets::triRdY));
    float dyG = static_cast<float>(read_register(RegisterOffsets::triGdY));
    float dyB = static_cast<float>(read_register(RegisterOffsets::triBdY));

    for(uint32_t y = y1; y <= y2; y++)
    {
        draw_line(static_cast<int>(left_x), y, static_cast<int>(right_x), y);

        left_x += dxdy1;
        right_x += dxdy2;

        startR = std::clamp(startR + dyR, 0.0f, 255.0f);
        startG = std::clamp(startG + dyG, 0.0f, 255.0f);
        startB = std::clamp(startB + dyB, 0.0f, 255.0f);
        write_register(RegisterOffsets::triStartR, static_cast<uint32_t>(startR));
        write_register(RegisterOffsets::triStartG, static_cast<uint32_t>(startG));
        write_register(RegisterOffsets::triStartB, static_cast<uint32_t>(startB));
    }
}

void PCU::draw_flat_top(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float dxdy1 = (static_cast<float>(x3) - static_cast<float>(x1)) / (static_cast<float>(y3) - static_cast<float>(y1));
    float dxdy2 = (static_cast<float>(x3) - static_cast<float>(x2)) / (static_cast<float>(y3) - static_cast<float>(y2));
    float left_x = x3;
    float right_x = left_x;

    float startR = static_cast<float>(read_register(RegisterOffsets::triStartR));
    float startG = static_cast<float>(read_register(RegisterOffsets::triStartG));
    float startB = static_cast<float>(read_register(RegisterOffsets::triStartB));
    float dyR = static_cast<float>(read_register(RegisterOffsets::triRdY));
    float dyG = static_cast<float>(read_register(RegisterOffsets::triGdY));
    float dyB = static_cast<float>(read_register(RegisterOffsets::triBdY));

    for(uint32_t y = y3; y > y1; y--)
    {
        draw_line(static_cast<int>(left_x), y, static_cast<int>(right_x), y);

        left_x -= dxdy1;
        right_x -= dxdy2;

        startR = std::clamp(startR + dyR, 0.0f, 255.0f);
        startG = std::clamp(startG + dyG, 0.0f, 255.0f);
        startB = std::clamp(startB + dyB, 0.0f, 255.0f);
        write_register(RegisterOffsets::triStartR, static_cast<uint32_t>(startR));
        write_register(RegisterOffsets::triStartG, static_cast<uint32_t>(startG));
        write_register(RegisterOffsets::triStartB, static_cast<uint32_t>(startB));
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
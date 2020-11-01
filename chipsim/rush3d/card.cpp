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
#include "card.h"

#include "log.hpp"

#define CARD_DEBUG

#define USE_SIM
#ifdef USE_SIM
Rush3D g_card;
#endif

static const char* register_names[] = {
    "STATUS",    "fbCOLOR",   "fbFILL",    "fbWIDTH", "fbHEIGHT", "vertexAx", "vertexAy", "vertexBx", "vertexBy", "vertexCx", "vertexCy", "triStartR",
    "triStartG", "triStartB", "triStartA", "triRdX",  "triGdX",   "triBdX",   "triAdX",   "triRdY",   "triGdY",   "triBdY",   "triAdY",   "cmdTriangle",
};

void Rush3D::initialize()
{
    m_monitor = SDL_CreateWindow("Rush3D Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0);
    m_screen = SDL_GetWindowSurface(m_monitor);
    m_pcu = new Chip::PCU(m_screen);
}

const SDL_Window* Rush3D::monitor() const
{
    return m_monitor;
}

const SDL_Surface* Rush3D::screen() const
{
    return m_screen;
}

void Rush3D::push_fifo(uint32_t command)
{
    m_pcu->push_fifo(command);
}

void Rush3D::flip() const
{
    m_pcu->swap_buffers();
}

void Rush3D::write_register(RegisterOffsets offset, uint32_t value)
{
#ifdef CARD_DEBUG
    log(LogLevel::INFO, "writing 0x%x to register %d(%s)\n", value, static_cast<int>(offset), register_names[offset]);
#endif
    m_pcu->write_register(offset, value);
}

uint32_t Rush3D::read_register(RegisterOffsets offset)
{
    return m_pcu->read_register(offset);
}
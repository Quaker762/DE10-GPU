/**
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
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
    log(LogLevel::INFO, "writing 0x%x to register %d\n", value, static_cast<int>(offset));
#endif
    m_pcu->write_register(offset, value);
}

uint32_t Rush3D::read_register(RegisterOffsets offset)
{
    return m_pcu->read_register(offset);
}
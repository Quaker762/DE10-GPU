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

#include "pcu.h"

#include <cstdint>
#include <queue>

// Emulated Video Card (the PCB containing both chips).
// This class acts as the 'arbiter'
class Rush3D
{
    friend class Chip::PCU;

public:
    Rush3D() { initialize(); }

    void write_register(RegisterOffsets offset, uint32_t value);
    uint32_t read_register(RegisterOffsets offset);

    void push_fifo(uint32_t);
    void flip() const;

    const SDL_Window* monitor() const;
    const SDL_Surface* screen() const;

private:
    void initialize();

private:
    Chip::PCU* m_pcu;

    SDL_Window* m_monitor; // Lol
    SDL_Surface* m_screen;
};
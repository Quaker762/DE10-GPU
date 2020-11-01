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
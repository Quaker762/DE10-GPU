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
 * Date: 11/9/2020
 */
#pragma once

#include <cstdint>

/**
 * ALTERA Bridge class. Defines member functions and values that a revelant to reading and
 * writing to the full or lightweight bridge on a CycloneV SOC. This class maintains
 * a single instance throughout the entire life of the program.
 *
 * This code is written specifically for QNX. If you want to use another Operating System,
 * you're on your own..
 */
class AlteraBridge
{
    enum class MAP_STATUS : int
    {
        OK = 0,
        FAILED
    };

public:
    AlteraBridge() = delete; // No default constructor
    AlteraBridge(uintptr_t device_address);

    ~AlteraBridge();

    static void initialize();
    void shutdown();

    void write(uint32_t offset, uint64_t data);

    uint64_t read(uint32_t offset) const;

    static AlteraBridge& the(); // Reference to static instantiation of this class

private:
    uintptr_t m_device_ptr{ 0 }; //
};

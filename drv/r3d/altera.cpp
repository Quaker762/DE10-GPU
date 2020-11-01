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
 * Altera Bridge Functionality
 *
 * Author: Jesse Buhagiar
 * Date: 11/9/2020
 */
#include "altera.h"

#include <cstdint>
#include <cstdlib>
#include <hw/inout.h>
#include <stdio.h>
#include <sys/mman.h>

static constexpr uint32_t RUSH3D_ADDRESS = 0xc0000000;
static constexpr uint8_t RUSH3D_ADDRESS_RANGE = 0x60;

static AlteraBridge* s_the = nullptr;

void AlteraBridge::initialize()
{
    s_the = new AlteraBridge(RUSH3D_ADDRESS); // Create a new bridge
}

void AlteraBridge::shutdown()
{
    if(s_the == nullptr)
        return;

    delete s_the;
}

AlteraBridge::~AlteraBridge()
{
    // Do munmap here!
}

AlteraBridge::AlteraBridge(uintptr_t device_address)
{
    // First, let's try to map the device
    uintptr_t mapping = mmap_device_io(RUSH3D_ADDRESS_RANGE, device_address);
    if(mapping == MAP_DEVICE_FAILED)
    {
        fputs("AlteraBridge: failed to map device!\n", stderr);
        exit(static_cast<int>(MAP_STATUS::FAILED));
    }

    m_device_ptr = mapping;
}

void AlteraBridge::write(uint32_t offset, uint64_t data)
{
    *reinterpret_cast<volatile uint64_t*>(m_device_ptr + offset) = data;
}

uint64_t AlteraBridge::read(uint32_t offset) const
{
    return *reinterpret_cast<volatile uint64_t*>(m_device_ptr + offset);
}

AlteraBridge& AlteraBridge::the()
{
    return *s_the;
}

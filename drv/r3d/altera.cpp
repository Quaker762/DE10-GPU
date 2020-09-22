/**
 * Altera Bridge functionality
 *
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
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
static constexpr uint8_t RUSH3D_ADDRESS_RANGE = 0x3f;

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

void AlteraBridge::write(uint32_t offset, uint32_t data)
{
    *reinterpret_cast<volatile uint64_t*>(m_device_ptr + offset) = data;
}

uint32_t AlteraBridge::read(uint32_t offset) const
{
    return *reinterpret_cast<volatile uint64_t*>(m_device_ptr + offset);
}

AlteraBridge& AlteraBridge::the()
{
    return *s_the;
}
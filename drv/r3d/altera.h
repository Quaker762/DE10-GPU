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

    inline void write(uint32_t offset, uint32_t data);
    inline void write(uint32_t offset, uint64_t data) = delete;

    inline uint32_t read(uint32_t offset) const;

    static AlteraBridge& the(); // Reference to static instantiation of this class

private:
    uintptr_t m_device_ptr{ 0 }; //
};
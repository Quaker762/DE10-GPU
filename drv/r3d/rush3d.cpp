/**
 * Altera Bridge functionality
 *
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 12/9/2020
 */

#include "rush3d.h"

#include "altera.h"
#include "tga.h"

#include <cstdio>
#include <cstdlib>
#include <sys/mman.h>
#include <sys/neutrino.h>

#define FRAMEBUFFER_SIZE 640 * 480 * 4

/**
 * Initialise the Rush3D driver (and any global state we need)
 */
int rush3d_card_init()
{
    AlteraBridge::initialize();

    return 0;
}

void rush3d_shutdown()
{
    AlteraBridge::the().shutdown();
}

void rush3d_register_write(uint32_t offset, uint64_t data)
{
    printf("register_write: writing 0x%llx to offset 0x%x\n", data, offset);
    AlteraBridge::the().write(offset, data);
}

uint64_t rush3d_register_read(uint32_t offset)
{
    return AlteraBridge::the().read(offset);
}

void rush3d_screenshot()
{
    // Let's map the framebuffer to a pointer that we can read..
    std::vector<uint32_t> data;
    uintptr_t framebuffer = mmap_device_io(FRAMEBUFFER_SIZE + 1, 0x38000000);
    if(framebuffer == MAP_DEVICE_FAILED)
    {
        fputs("rush3d_screenshot: failed to mape framebuffer!\n", stderr);
        abort();
    }

    // Hahahaha, pixel loop go brrrrrrr
    size_t count = FRAMEBUFFER_SIZE / 4;
    volatile uint32_t* fb_ptr = reinterpret_cast<volatile uint32_t*>(framebuffer);
    while(count)
    {
        uint32_t pixel = *fb_ptr++;
        pixel |= 0xff000000; // Make sure it's not transparent!
        data.push_back(pixel);
        count--;
    }

    tga_write_file(data);
    munmap_device_io(framebuffer, FRAMEBUFFER_SIZE);
}

void rush3d_swap_buffers()
{
    rush3d_register_write(CONTROL_STATUS_REGISTER, SWAP_FRAMEBUFFER);
    while(static_cast<volatile uint64_t>(rush3d_register_read(CONTROL_STATUS_REGISTER) & SWAP_FRAMEBUFFER))
        ;
}

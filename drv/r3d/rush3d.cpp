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

#include <cstdio>
#include <cstdlib>
#include <sys/neutrino.h>

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

void rush3d_register_write(uint32_t offset, uint32_t data)
{
    AlteraBridge::the().write(offset, data);
}

uint32_t rush3d_register_read(uint32_t offset)
{
    return AlteraBridge::the().read(offset);
}
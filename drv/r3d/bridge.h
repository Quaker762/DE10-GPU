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
 *
 * Altera Lightweight bridge interface
 *
 * This file contains the interface to set up and manipulate the lightweight bridge
 * via mapping the address range 0xff20 0000 to a writable pointer. This way
 * it is possible to write the custom FPGA peripheral.
 *
 * Author: Jesse Buhagiar
 * Date: 2-6-2019
 */
#ifndef _BRIDGE_H_
#define _BRIDGE_H_

#include <stdint.h>

/**
 *  Initialise the lightweight bridge
 */
void bridge_init();

/**
 *  Write a value to a port. Note that the variable
 *  'value' is truncated to 16-bits.
 *
 *  @param port     Port we want to write to
 *  @param value    The value we want to write to this port
 */
void write_port(uint8_t port, uint32_t value);

/**
 * Read a value from a port
 *
 * @param port Port we want to read from
 *
 * @return The value latched at IO port `port`
 */
uint32_t read_port(uint8_t port);

#endif

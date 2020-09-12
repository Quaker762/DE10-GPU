/**
 *  Altera Lightweight bridge interface
 *
 *  This file contains the interface to set up and manipulate the lightweight bridge
 *  via mapping the address range 0xff20 0000 to a writable pointer. This way
 *  it is possible to write the custom FPGA peripheral.
 *
 *  @date   2-6-2019
 *  @autho  Jesse Buhagiar
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

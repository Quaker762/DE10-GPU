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
 * Register definition file.
 *
 * Contains all register offsets, as well as number of registers
 * contained in the SUPERIO ISA controller.
 *
 * Author: Jesse Buhagiar
 * Date: 2-6-2019
 */
#ifndef _REGISTER_H_
#define _REGISTER_H_

#define VERTEX_A_L 0x00
#define VERTEX_A_H 0x01

#define VERTEX_B_L 0x02
#define VERTEX_B_H 0x03

#define VERTEX_C_L 0x04
#define VERTEX_C_H 0x05

#define BACK_COLOUR 0x06

#define CONTROL_STATUS_L 0x08
#define CONTROL_STATUS_H 0x09

#endif

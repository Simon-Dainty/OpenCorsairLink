/*
 * This file is part of OpenCorsairLink.
 * Copyright (C) 2017  Sean Nelson <audiohacked@gmail.com>

 * OpenCorsairLink is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.

 * OpenCorsairLink is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with OpenCorsairLink.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include "../../lowlevel/asetek4.h"
#include "../../device.h"
#include "core.h"

int corsairlink_asetek_pump_mode(struct corsair_device_info *dev, uint8_t pump_mode)
{
	int r;
	uint8_t response[32];
	uint8_t commands[32] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = PumpMode;

	if (pump_mode == PERFORMANCE)
		commands[1] = Asetek_Performance;
	else if (pump_mode == QUIET)
		commands[1] = Asetek_Quiet;

	r = dev->driver->write(dev->handle, dev->write_endpoint, commands, 2);
	r = dev->driver->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

// int corsairlink_asetek_pump_mode_performance(struct corsair_device_info *dev)
// {
// 	int r;
// 	uint8_t response[32];
// 	uint8_t commands[32] ;
// 	memset(response, 0, sizeof(response));
// 	memset(commands, 0, sizeof(commands));
// 	commands[0] = PumpMode;
// 	commands[1] = Asetek_Performance;
//
// 	r = dev->driver->write(dev->handle, dev->write_endpoint, commands, 2);
// 	r = dev->driver->read(dev->handle, dev->read_endpoint, response, 32);
//
// 	return r;
// }
//
// int corsairlink_asetek_pump_mode_quiet(struct corsair_device_info *dev)
// {
// 	int r;
// 	uint8_t response[32];
// 	uint8_t commands[32] ;
// 	memset(response, 0, sizeof(response));
// 	memset(commands, 0, sizeof(commands));
// 	commands[0] = PumpMode;
// 	commands[1] = Asetek_Quiet;
//
// 	r = dev->driver->write(dev->handle, dev->write_endpoint, commands, 2);
// 	r = dev->driver->read(dev->handle, dev->read_endpoint, response, 32);
//
// 	return r;
// }

/*
 * This file is part of OpenCorsairLink.
 * Copyright (C) 2014  Sean Nelson <audiohacked@gmail.com>

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Proto.h"
#include "Link.h"
#include "Temperature.h"

extern CorsairLink *cl;

int CorsairTemp::SelectSensor(int index)
{
	memset(cl->buf,0x00,sizeof(cl->buf));

	cl->buf[0] = 0x04; // Length
	cl->buf[1] = cl->CommandId++; // Command ID
	cl->buf[2] = WriteOneByte; // Command Opcode
	cl->buf[3] = TEMP_SelectActiveSensor; // Command data...
	cl->buf[4] = index;

	int res = hid_write(cl->handle, cl->buf, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, cl->buf);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	return cl->buf[2];
}

int CorsairTemp::CurrentSensor()
{
	memset(cl->buf,0x00,sizeof(cl->buf));

	cl->buf[0] = 0x03; // Length
	cl->buf[1] = cl->CommandId++; // Command ID
	cl->buf[2] = ReadOneByte; // Command Opcode
	cl->buf[3] = TEMP_SelectActiveSensor; // Command data...

	int res = hid_write(cl->handle, cl->buf, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, cl->buf);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	return cl->buf[2];
}

int CorsairTemp::GetTempSensors()
{//1
	memset(cl->buf,0x00,sizeof(cl->buf));
	// Read fan Mode
	cl->buf[0] = 0x03; // Length
	cl->buf[1] = cl->CommandId++; // Command ID
	cl->buf[2] = ReadOneByte; // Command Opcode
	cl->buf[3] = TEMP_CountSensors; // Command data...

	int res = hid_write(cl->handle, cl->buf, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, cl->buf);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	return cl->buf[2];
}

int CorsairTemp::GetTemp()
{//2
	memset(cl->buf,0x00,sizeof(cl->buf));
	// Read fan Mode
	cl->buf[0] = 0x03; // Length
	cl->buf[1] = cl->CommandId++; // Command ID
	cl->buf[2] = ReadTwoBytes; // Command Opcode
	cl->buf[3] = TEMP_Read; // Command data...

	int res = hid_write(cl->handle, cl->buf, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, cl->buf);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}
	int temp = cl->buf[3]<<8;
	temp += cl->buf[2];
	return temp;
}

int CorsairTemp::GetTempLimit()
{//2
	memset(cl->buf,0x00,sizeof(cl->buf));
	// Read fan Mode
	cl->buf[0] = 0x03; // Length
	cl->buf[1] = cl->CommandId++; // Command ID
	cl->buf[2] = ReadTwoBytes; // Command Opcode
	cl->buf[3] = TEMP_Limit; // Command data...

	int res = hid_write(cl->handle, cl->buf, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, cl->buf);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	int limit = cl->buf[5]<<8;
	limit += cl->buf[4];

	return limit;
}

int CorsairTemp::SetTempLimit(int limit)
{//2
	memset(cl->buf,0x00,sizeof(cl->buf));
	// Read fan Mode
	cl->buf[0] = 0x05; // Length
	cl->buf[1] = cl->CommandId++; // Command ID
	cl->buf[2] = WriteTwoBytes; // Command Opcode
	cl->buf[3] = TEMP_Limit; // Command data...
	cl->buf[4] = limit & 0x00FF;
	cl->buf[5] = limit >> 8;

	int res = hid_write(cl->handle, cl->buf, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, cl->buf);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		return -1;
	}

	return 0;
}

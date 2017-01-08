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

int print(enum msglevel level, const char *fmt, ...)
{
	va_list ap;
	int ret = 0;
	FILE *output_type = stdout;

	if (level < MSG_INFO)
		output_type = stderr;

	if (level <= verbose_screen) {
		va_start(ap, fmt);
		ret = vfprintf(output_type, fmt, ap);
		va_end(ap);
		/* msg_*spew often happens inside chip accessors in possibly
		 * time-critical operations. Don't slow them down by flushing. */
		if (level != MSG_SPEW)
			fflush(output_type);
	}

	if ((level <= verbose_logfile) && logfile) {
		va_start(ap, fmt);
		ret = vfprintf(logfile, fmt, ap);
		va_end(ap);
		if (level != MSG_SPEW)
			fflush(logfile);
	}

	return ret;
}

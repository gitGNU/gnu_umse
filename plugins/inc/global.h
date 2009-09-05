/*

    global.h
    Copyright (c) 2009 KERNEL_ERROR <k3rn3l.3rr0r(at)gmail[dot]com>
    =============================================================
    
    This file is part of UMSE.

    UMSE is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    UMSE is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with UMSE.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef _GLOBAL_H
#	define _GLOBAL_H
	
	#define		FMT_LITTLE_ENDIAN	1
	#define		FMT_BIG_ENDIAN		2

	typedef unsigned int uint;

	typedef struct input_data
	{
		int bits;
		int rate;
		int channels;
		int format;
		char *buffer;
		uint buffer_size;
		char author[128];
		char title[128];
		uint lenght;
		uint ntracks;
		uint ctrack;
	}input_data_t, *pinput_data_t;


	typedef struct input_func
	{
		uint (*init)( pinput_data_t data , char * filename);
		unsigned char (*play)( pinput_data_t data );
		uint (*stop)(void);
		uint (*next_track)( pinput_data_t data );
		uint (*prev_track)( pinput_data_t data );
		uint (*close)(void);
	}input_func_t , *pinput_func_t;


#endif

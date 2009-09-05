/*

    input.h
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

#ifndef _INPUT_H
#	define _INPUT_H
	
	#define		FMT_LITTLE_ENDIAN	AO_FMT_LITTLE
	#define		FMT_BIG_ENDIAN		AO_FMT_BIG

	pinput_t input_plugin_create ( char *path );
	void input_plugin_init ( pinput_t input );
	uint is_supported ( pinput_t input , char *ext );
	byte input_plugin_play ( poutput_t output , pinput_t input , char * filename , WINDOW *description );
	byte input_plugin_playing ( pinput_t input );
	void input_plugin_ntrack ( pinput_t input );
	void input_plugin_ptrack ( pinput_t input );
	void input_plugin_write ( void * ptrdata );
	void input_plugin_stop ( poutput_t output , pinput_t input );
	void input_plugin_destroy ( pinput_t input );



#endif

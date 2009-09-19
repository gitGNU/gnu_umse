/*

    sc68-plugin.c
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

#include "sc68-plugin.h"

sc68_init_t init68;
sc68_create_t create68;
sc68_music_info_t info;
sc68_t * sc68 = NULL;
char buffer[512*4];


unsigned int
 libsc68_init ( data , filename )
 	pinput_data_t data;
	char *filename;
{
	memset ( &init68 , 0 , sizeof ( sc68_init_t ) );
	memset ( &create68 , 0 , sizeof ( sc68_create_t ) );
	
	init68.argc = 0;
	init68.argv = NULL;
	
	if ( sc68_init ( &init68 ) )
		return 2;
	
	if ( !(sc68 = sc68_create ( &create68 )) )
	{
		sc68_shutdown ();
		return 3;
	}
	
	if ( sc68_load_url ( sc68 , filename ) )
	{
		sc68_destroy ( sc68 );
		sc68_shutdown ();
		return 6;
	}

	data->buffer = buffer;
	data->buffer_size = sizeof ( buffer );

	data->ctrack = 1;
	sc68_music_info ( sc68 , &info , data->ctrack , NULL );
	data->ntracks = sc68_tracks ( sc68 );
	data->lenght = info.time_ms;
	snprintf ( data->author , sizeof ( data->author ) , "%s" , info.author );
	snprintf ( data->title , sizeof ( data->title ) , "%s" , info.title );

	sc68_play ( sc68 , data->ctrack , 1 );
	return 1;
}

unsigned char
 libsc68_play ( data )
 	pinput_data_t data;
{
	if( !(sc68_process ( sc68 , buffer , sizeof ( buffer)  >> 2 ) & SC68_END) )
		return 1;
	else
		return 0;
}

unsigned int
 libsc68_next_track ( data )
 	pinput_data_t data;
{
	if ( data->ctrack != data->ntracks )
	{
		data->ctrack++;
		sc68_play ( sc68 , data->ctrack , 1 );
	}
	return 0;	
}

unsigned int
 libsc68_prev_track ( data )
 	pinput_data_t data;
{
	if ( data->ctrack != 1 )
	{
		data->ctrack--;
		sc68_play ( sc68 , data->ctrack , 1 );
	}
	return 0;	
}

unsigned int 
 libsc68_stop ( void )
{
	sc68_stop ( sc68 );
	return 0;	
}

unsigned int
 libsc68_close ( void )
{
	sc68_destroy ( sc68 );
	sc68_shutdown ( );
	return 0;	
}



input_func_t input_functions = {
	.init = libsc68_init,
	.play = libsc68_play,
	.stop = libsc68_stop,
	.next_track = libsc68_next_track,
	.prev_track = libsc68_prev_track,
	.close = libsc68_close
};



char input_extensions[] = "sndh;sc68;snd;";


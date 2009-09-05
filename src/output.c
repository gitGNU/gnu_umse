/*

    output.c
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

#include "global.h"


poutput_t
 output_create ( void )
{
	poutput_t output;
	output = ( poutput_t ) calloc ( 1 , sizeof ( output_t ) );
	output->opened = 0;
	return output;
}

void
 output_initialize ( output , bits , rate , channels , byte_format )
	poutput_t output;
	int bits;
	int rate;
	int channels;
	int byte_format;
{
	ao_initialize ( );
	
	output->def_audio_driver = ao_default_driver_id ();
	output->audio_format.bits = bits;
	output->audio_format.rate = rate;
	output->audio_format.channels = channels;
	output->audio_format.byte_format = byte_format;
	
	output->audio_device = ao_open_live ( output->def_audio_driver , &output->audio_format , NULL );
	
	if ( output->audio_device == NULL )
	{ free ( output ); return; }

	output->opened = 1;
	return;
}

void
 output_write ( output , buffer , buffer_size )
	poutput_t output;
	char * buffer;
	uint buffer_size;
{
	ao_play ( output->audio_device , (void *) buffer , buffer_size );
}

void
 output_close ( output )
	poutput_t output;
{
	if (output->audio_device != NULL)
		ao_close ( output->audio_device );
	ao_shutdown();
}

void
 output_free ( output )
	poutput_t output;
{
	ao_shutdown ();
	free ( output );
}


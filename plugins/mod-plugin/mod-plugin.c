/*

    mod-plugin.c
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

#include "mod-plugin.h"

ModPlugFile *file;
char abuffer[512*4];

unsigned int
 mod_init ( data , filename )
 	pinput_data_t data;
	char *filename;
{
	FILE *bfile;
	char *buffer = NULL;
	unsigned long length = 0;
	ModPlug_Settings settings;

	bfile = fopen ( filename , "rb+" );
	if ( bfile == NULL )
		return 2;
	fseek ( bfile , 0 , SEEK_END );
	length = ftell ( bfile );
	fseek ( bfile , 0 , SEEK_SET );
	buffer = (char*) calloc ( length , sizeof ( char ) );
	if ( buffer == NULL )
	{
		flcose ( bfile );
		return 3;
	}
	fread ( buffer , sizeof ( char ) , length , bfile );
	fclose ( bfile );
	
	file = ModPlug_Load ( buffer , length );
	free ( buffer );
	
	data->buffer = abuffer;

	data->buffer_size = sizeof ( abuffer );

	data->ctrack = 1;
	data->ntracks = 1; /* No multiple track in this format. */

	snprintf ( data->author , sizeof ( data->author ) , ""  );
	snprintf ( data->title , sizeof ( data->title ) , "" );

	return 1;
}

unsigned char
 mod_play ( data )
 	pinput_data_t data;
{
	if ( ModPlug_Read ( file , abuffer , sizeof ( abuffer ) ) < 0 )
		return 0;
	else
		return 1;
	return 0;
}

unsigned int
 mod_prev_track ( data )
 	pinput_data_t data;
{
	/* No multiple track in this format. */
	return 0;
}

unsigned int
 mod_next_track ( data )
 	pinput_data_t data;
{
	/* No multiple track in this format. */
	return 0;
}


unsigned int
 mod_stop ( data )
 	pinput_data_t data;
{
	return 0;
}

unsigned int 
 mod_close ( data )
 	pinput_data_t data;
{
	ModPlug_Unload ( file );
	return 0;
}

input_func_t input_functions = {
	.init = mod_init,
	.play = mod_play,
	.stop = mod_stop,
	.next_track = mod_next_track,
	.prev_track = mod_prev_track,
	.close = mod_close
};

char input_extensions[] = "mod;s3m;xm;it;669;amf;ams;dbm;dmf;dsm;"
			"far;mdl;med;mtm;okt;ptm;stm;ult;umx;mt2;"
			"psm;mdz;s3z;xmz;itz;mdr;s3r;xmr;itr;mdgz;"
			"s3gz;xmgz;itgz;";


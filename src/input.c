/*

    input.c
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

pinput_t
 input_plugin_create ( path )
 	char *path;
{
	pinput_t input;
	input = calloc ( 1 , sizeof ( input_t ) );
	snprintf ( input->plugin_directory , PATH_MAX , "%s/.umse/plugins" , path );
	input->plugin_running = 0;
	input->plugin_load = 0;
	return input;
}

void
 input_plugin_init ( input )
 	pinput_t input;
{
	char /*err[256],*/ file[256];
	void *handle = NULL; char * ext, *ip_ext;
	DIR *plug; struct dirent * plugdir; 
	uint np = 0, lext = 0;

	input->cext = 0;

	np = nfiles ( input->plugin_directory , ".so" );

	input->ext = (char **) calloc ( np+1 , sizeof ( char *) );
	
	if ( !np )
	{
		free ( input->ext );
		return;
	}

	plug = opendir ( input->plugin_directory );
	while ( (plugdir = readdir ( plug )) != NULL )
	{
		ext = strchr ( plugdir->d_name , '.' );

		if ( ext == NULL )
			continue;

		if ( strcmp ( ext , ".so" ) )
			continue;

		snprintf ( file , sizeof ( file ) , "%s/%s" , input->plugin_directory , plugdir->d_name );

		handle = dlopen ( file , RTLD_LAZY );

		if ( handle == NULL )
			continue;

		ip_ext = dlsym ( handle , "input_extensions" );
		/* ip_funcs = dlsym ( ... ); */

		lext = strlen ( ip_ext ) + strlen ( plugdir->d_name ) + 2;

		input->ext[input->cext] = (char *) calloc ( lext , sizeof ( char ) );
		snprintf ( input->ext[input->cext] , lext , "%s:%s" , plugdir->d_name , ip_ext );

		dlclose ( handle );

		input->cext++;
	}

	closedir ( plug );
}

uint
 is_supported ( input , ext )
 	pinput_t input;
	char *ext;
{
	char tmp[256],sext[256];
	char *cstr = NULL;
	uint i , start = 0 , cpos = 0;
	for ( i = 0; i < input->cext ; i++ )
	{
		cstr = strchr ( input->ext[i] , ':' )+1;
		if ( cstr == NULL )
			continue;
		snprintf ( tmp , sizeof ( tmp ) , "%s" , cstr );
		while ( ( cpos = strbrkidx ( tmp , ';' , start ) ) != -1 )
		{
			splitstr ( tmp , sext , sizeof ( sext ) , ';' , cpos );
			start++;
			if ( !strcmp ( sext , ext ) )
				return i;
		}
		start = 0;
	}
	return ~(0);
}

byte
 input_plugin_load ( input , ext )
 	pinput_t input;
	char *ext;
{
	uint p = 0; char *ptr = NULL;
	char file[256],tmp[256];
	p = is_supported ( input , ext );
	if ( p == -1 )
		return 0;
	/* NOT SECURE */
	ptr = strchr ( input->ext[p] , ':' );
	memcpy ( tmp , input->ext[p] , ptr-input->ext[p] );
	tmp[ptr-input->ext[p]] = 0;
	snprintf ( file , sizeof ( file ) , "%s/%s" , input->plugin_directory , tmp );
	input->plugin_handle = dlopen ( file , RTLD_LAZY );
	if ( input->plugin_handle == NULL )
		return 0;
	input->funcs = dlsym ( input->plugin_handle , "input_functions" );
	return 1;
}

byte
 input_plugin_play ( output , input , filename , description )
 	poutput_t output;
	pinput_t input;
	char *filename;
	WINDOW *description;
{
	char *fext = NULL;
	if ( input->plugin_load )
		input_plugin_stop ( output , input );
	fext = strchr ( filename , '.' )+1;
	if ( input_plugin_load ( input , fext ) )
		input->plugin_load = 1;
	else
		return 0;
	//output_initialize ( output , 16 , 44100 , 2 , AO_FMT_LITTLE );
	if ( input->funcs->init ( &input->data , filename ) > 1 )
		return 0;
	output_initialize ( output , 16 , 44100 , 2 , AO_FMT_LITTLE );
	input->ptr = output;
	pthread_create ( &input->thread , NULL , ( void * ) input_plugin_write , ( void * )input );
	input->plugin_running = 1;

	werase ( description );
	if ( strcmp ( input->data.author , "" ) )
		mvwprintw ( description , 0 , 0 , "[%d/%d] %s - %s" , input->data.ctrack , input->data.ntracks , input->data.author , input->data.title );
	else
		mvwprintw ( description , 0 , 0 , "[%d/%d] Unknown" , input->data.ctrack , input->data.ntracks );
	return 1;
	
}

void
 input_plugin_write ( ptrdata )
 	void *ptrdata;
{
	pinput_t input = ( pinput_t ) ptrdata;
	while ( input->plugin_running )
	{
		if ( input->funcs->play( &input->data ) )
			output_write ( input->ptr , input->data.buffer , input->data.buffer_size );
		else
			break;
	}
	return;
}

byte
 input_plugin_playing ( input )
 	pinput_t input;
{ return input->plugin_running; }

void
 input_plugin_ntrack ( input , description )
 	pinput_t input;
	WINDOW *description;
{
	input->funcs->next_track ( &input->data );
	werase ( description );
	mvwprintw ( description , 0 , 0 , "[%d/%d] %s - %s" , input->data.ctrack , input->data.ntracks , input->data.author , input->data.title );

}

void
 input_plugin_ptrack ( input , description )
 	pinput_t input;
	WINDOW *description;
{
	input->funcs->prev_track ( &input->data );
	werase ( description );
	mvwprintw ( description , 0 , 0 , "[%d/%d] %s - %s" , input->data.ctrack , input->data.ntracks , input->data.author , input->data.title );

}

void
 input_plugin_stop ( output , input )
 	poutput_t output;
 	pinput_t input;
{
	if ( input->plugin_running )
	{
		input->funcs->stop();
		input->plugin_running = 0;
		pthread_join ( input->thread , NULL );
		output_close ( output );
		input->funcs->close();
	}
	if ( input->plugin_load )
		dlclose ( input->plugin_handle );
	input->plugin_load = 0;
}

void
 input_plugin_destroy ( input )
 	pinput_t input;
{
	if ( input->cext > 0 )
	{
		uint i;
		for ( i = 0; i < input->cext ; i++ )
			free ( input->ext[i] );
		free ( input->ext );
	}
	free ( input );
}


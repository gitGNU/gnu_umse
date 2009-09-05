/*

    struct.h
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

#ifndef _STRUCT_H
#	define _STRUCT_H

	typedef unsigned char byte;
	typedef unsigned int uint;
	
	enum {
		COLORS_DEFAULT=1 , COLORS_TITLEBAR , COLORS_LISTVIEW , COLORS_HIGHLISTVIEW ,
		COLORS_SEL , COLORS_HIGHSEL , COLORS_DESC
	};
	
	typedef struct theme
	{
		short default_fore; short default_bkgd;
		short titlebar_fore; short titlebar_bkgd;
		short listview_fore; short listview_bkgd;
		short highlistview_fore; short highlistview_bkgd;
		short sel_fore; short sel_bkgd;
		short highsel_fore; short highsel_bkgd;
		short desc_fore; short desc_bkgd;
	}theme_t, *ptheme_t;
	
	typedef struct listview
	{
		WINDOW *window;
		WINDOW **items;
		char **s_items;
		int *attr;
		uint nwin;
		uint nitems;
		uint citem;
		uint nrealloc;
		uint selected_item;
		uint highlight_item;
		uint width;
		uint height;
		uint sitem;
		uint show_num;
	}listview_t, *plistview_t;
	
	
	typedef struct config
	{
		char p_home[512];
		char p_logo[512];
		char p_plugins[512];
	}config_t , *pconfig_t;
	
	
	typedef struct output
	{
		ao_device *audio_device;
		int def_audio_driver;
		ao_sample_format audio_format;
		byte opened;
	}output_t, *poutput_t;

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
		uint length;
		uint ntracks;
		uint ctrack;
	}input_data_t, *pinput_data_t;

	typedef struct input_func
	{
		unsigned int (*init)(pinput_data_t data,char*filename);
		unsigned char (*play)(pinput_data_t data);
		unsigned int (*stop)(void);
		unsigned int (*next_track)( pinput_data_t data );
		unsigned int (*prev_track)( pinput_data_t data );
		unsigned int (*close)(void);
	}input_func_t , *pinput_func_t;
	
	typedef struct input
	{
		char plugin_directory[PATH_MAX];
		pinput_func_t funcs;
		char **ext;
		input_data_t data;
		uint cext;
		void *plugin_handle;
		byte plugin_running;
		byte plugin_load;
		poutput_t ptr;
		pthread_t thread;
		pthread_mutex_t tlock;
		WINDOW *desc;
	}input_t , *pinput_t;
	
#endif


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

	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <string.h>
	#include <unistd.h>
	#include <dirent.h>
	#include <dlfcn.h>
	#include <pwd.h>
	#include <sys/stat.h>
	#include <linux/limits.h>
	#include <ncurses.h>
	#include <panel.h>
	#include <ao/ao.h>
	#include <pthread.h>

	#include "struct.h"
	#include "str.h"
	#include "config.h"
	#include "screen.h"
	#include "static.h"
	#include "sys.h"
	#include "file.h"
	#include "listview.h"
	#include "output.h"
	#include "input.h"
	#include "browse.h"

	#define KEY_TAB			9
	#define KEY_RETURN		10
	
	#define	MAX_FILE_NAME		256
	
	#define true			1
	#define false			0
	
	#define LISTVIEW_NONE		~(0)
	#define LISTVIEW_UP		1
	#define LISTVIEW_DOWN		2
	
	#define	STATIC_NORMAL		1
	#define STATIC_CENTER		2
	#define	STATIC_HCENTER		3
	#define STATIC_VCENTER	 	4
	
	#define NWORKSPACE		4
	#define WORKSPACE_DEFAULT	1
	#define WORKSPACE_BROWSE	2
	#define WORKSPACE_PLAYLIST	3
	#define WORKSPACE_ABOUT		4
	
	#define ALLOC_MEM		50

	/* #define NAGSCREEN */
	#define NAG_TIME		2
	
	
	#ifdef _RELEASE_
	#	define _LEVEL_		"prototype"
	#	define _VERSION_	"0.0.001"
	#	define _RVERSION_	"Unix Multi-Soundchip Emulator v." _VERSION_ "(" _LEVEL_ ")"
	#else
	#	define _RVERSION_	"Unix Multi-Soundchip Emulator (prototype version)"
	#endif
	
	#define CTRL(c) \
		((c) & 037)
		
	#define BROWSE_TITLE		"Browse"
	#define PLAYLIST_TITLE		"Playlist"
	#define ABOUT_TITLE		_RVERSION_
		
		
	#define _ABOUT_			_RVERSION_ "\n" \
					"UMSE is a text-mode music player for GNU/Linux\n" \
					"and other UNIX like operation system.\n" \
					"Code: KERNEL_ERROR       Ascii: (unknown)\n"
	

#endif

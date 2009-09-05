/*

    screen.c
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

void
 screen_init ( void )
{
	initscr ();
	noecho ();
	cbreak ();
	curs_set ( 0 );
	keypad ( stdscr , TRUE );
}

void
 screen_colors ( theme )
	ptheme_t theme;
{
	start_color ();
	use_default_colors ();
	
	init_pair ( COLORS_DEFAULT , theme->default_fore , theme->default_bkgd );
	init_pair ( COLORS_TITLEBAR , theme->titlebar_fore , theme->titlebar_bkgd );
	init_pair ( COLORS_LISTVIEW , theme->listview_fore , theme->listview_bkgd );
	init_pair ( COLORS_HIGHLISTVIEW , theme->highlistview_fore , theme->highlistview_bkgd );
	init_pair ( COLORS_SEL , theme->sel_fore , theme->sel_bkgd );
	init_pair ( COLORS_HIGHSEL , theme->highsel_fore , theme->highsel_bkgd );
	init_pair ( COLORS_DESC , theme->desc_fore , theme->desc_bkgd );
}

void
 screen_destroy ( void )
{
	endwin ();
}

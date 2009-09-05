/*

    static.c
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


WINDOW *
 static_window_create ( width , height , x , y  , text , t_align , t_color , boxwin )
	uint width;
	uint height;
	uint x;
	uint y;
	const char *text;
	byte t_align;
	int t_color;
	byte boxwin;
{
	WINDOW *win;
	uint nl = getnchar ( (char *)text , '\n' )+1, cpos = 0 , start = 0;
	char tmp[1024]; uint count = 0;
	
	win = newwin ( height , width , y , x );
	wbkgd ( win , COLOR_PAIR ( t_color ) );
	refresh();
	
	wattrset ( win , A_BOLD );
	
	switch ( t_align )
	{
		case STATIC_NORMAL:
			wprintw ( win  , "%s" , text );
			break;
		
		case STATIC_VCENTER:
			mvwprintw ( win , (height-nl)/2 , 0 , "%s" , text );
			break;
		
		case STATIC_HCENTER:
		{
			while ( ( cpos = strbrkidx ( (char*)text , '\n' , start ) ) != -1 )
			{
				splitstr ( (char*)text , tmp , sizeof ( tmp ) , '\n' , cpos );
				start++;
				mvwprintw ( win , count++ , ((width-strlen(tmp))/2) , "%s" , tmp );
			}
			break;
		}
		
		case STATIC_CENTER:
		{
			while ( ( cpos = strbrkidx ( (char*)text , '\n' , start ) ) != -1 )
			{
				splitstr ( (char*)text , tmp , sizeof ( tmp ) , '\n' , cpos );
				start++;
				mvwprintw ( win , ((height-nl)/2)+count++ , ((width-strlen(tmp))/2) , "%s" , tmp );
			}
			break;
		}
	}
	
	if ( boxwin )
		box ( win , ACS_VLINE , ACS_HLINE );
	
	return win;
}

WINDOW *
 static_window_create_child ( parent , width , height , x , y  , text , t_align , t_color , boxwin )
	WINDOW *parent;
	uint width;
	uint height;
	uint x;
	uint y;
	const char *text;
	byte t_align;
	int t_color;
	byte boxwin;
{
	WINDOW *win;
	uint nl = getnchar ( (char *)text , '\n' )+1, start = 0 , cpos = 0;
	char tmp[1024]; uint count = 0;
	
	win = derwin ( parent , height , width , y , x );
	wbkgd ( win , COLOR_PAIR ( t_color ) );
	refresh();
	
	switch ( t_align )
	{
		case STATIC_NORMAL:
			wprintw ( win  , "%s" , text );
			break;
		
		case STATIC_VCENTER:
			mvwprintw ( win , (height-nl)/2 , 0 , "%s" , text );
			break;
		
		case STATIC_HCENTER:
		{
			while ( ( cpos = strbrkidx ( (char*)text , '\n' , start ) ) != -1 )
			{
				splitstr ( (char*)text , tmp , sizeof ( tmp ) , '\n' , cpos );
				start++;
				mvwprintw ( win , count++ , ((width-strlen(tmp))/2) , "%s" , tmp );
			}
			break;
		}
		
		case STATIC_CENTER:
		{
			while ( ( cpos = strbrkidx ( (char*)text , '\n' , start ) ) != -1 )
			{
				splitstr ( (char*)text , tmp , sizeof ( tmp ) , '\n' , cpos );
				start++;
				mvwprintw ( win , ((height-nl)/2)+count++ , ((width-strlen(tmp))/2) , "%s" , tmp );
			}
			break;
		}
	}
	
	if ( boxwin )
		box ( win , ACS_VLINE , ACS_HLINE );
	
	return win;
}


void
 static_set ( swin , str )
 	WINDOW *swin;
	char *str;
{
	werase ( swin );
	mvwprintw ( swin , 0 , 0 , str );
}

void
 static_update ( swin )
	WINDOW *swin;
{
	wrefresh ( swin );
}

void
 static_redraw ( swin )
	WINDOW *swin;
{
	redrawwin ( swin );
	wrefresh ( swin );
}

void
 static_window_destroy ( swin )
	WINDOW *swin;
{
	delwin ( swin );
	refresh ();
}

/*

    sys.h
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
 nagscreen ( logo )
	const char * logo;
{
	WINDOW *nag;
	FILE *flogo;
	char buffer[1024];
	unsigned int line = 2, maxx = getmaxx ( stdscr );
	
	nag = newwin ( getmaxy ( stdscr ) , getmaxx ( stdscr ) , 0 , 0 );
	wbkgd ( nag , COLOR_PAIR ( COLORS_DEFAULT ) );
	box ( nag , ACS_VLINE , ACS_HLINE );
	
	if ( (flogo = fopen ( logo , "rb" )) != NULL )
	{
		while ( fgets ( buffer , sizeof ( buffer ) , flogo ) != NULL )
		{
			if ( strlen ( buffer ) > 1 )
			{
				buffer[strlen(buffer)-1]=0;
				mvwaddstr ( nag , line , (maxx-strlen(buffer))/2 , buffer );
			}
			line++;
		}
		fclose ( flogo );
	}
	else
		mvwprintw ( nag , (getmaxy(stdscr))-2 , 2 , "Error: Can't read logo: \'%s\'." , logo );
	wrefresh ( nag );
	
	/* NAG NAG NAG! */
	sleep ( NAG_TIME );
	delwin ( nag );
	refresh ( );
}

void
 popup ( title , text )
	char * title;
	char * text;
{
	WINDOW *pop; char tmp[512]; uint yt = 3;
	uint nl = getnchar ( text , '\n' ) , cpos = 0 , start = 0;
	uint width = strlen(text)+4, height = nl+7;
	pop = newwin ( height , width , (stdscr->_maxy-height)/2 , (stdscr->_maxx-width)/2 );
	refresh ();
	box ( pop , ACS_VLINE , ACS_HLINE );
	mvwhline ( pop , 2 , 1 , ACS_HLINE , width-2 );
	mvwprintw ( pop , 1 , 1 , "%s" , title );
	while ( ( cpos = strbrkidx ( text , '\n' , start ) ) != -1 )
	{
		splitstr ( text , tmp , sizeof ( tmp ) , '\n' , start );
		start++;
		mvwprintw ( pop , yt++ , 2 , "%s" , tmp );
	}
	mvwprintw ( pop , yt+1 , (width-16)/2 , "<Press any key>" );
	wrefresh ( pop );
	getch ();
	delwin ( pop );
	redrawwin ( stdscr );
	update_panels ();
	refresh();
}

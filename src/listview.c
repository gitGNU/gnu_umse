/*

    listview.c
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

plistview_t
 listview_create ( width , height , x , y , sn )
	uint width;
	uint height;
	uint x;
	uint y;
	byte sn;
{
	plistview_t list;
	list = ( plistview_t ) calloc ( 1 , sizeof ( listview_t ) );
	if ( list == NULL )
		return NULL;
	list->width = width;
	list->height = height;
	list->window = newwin ( list->height , list->width , y , x );
	wbkgd ( list->window , COLOR_PAIR ( COLORS_LISTVIEW ) );
	refresh();
	list->show_num = sn;
	return list;
}

plistview_t
 listview_create_child ( parent , width , height , x , y , sn )
	WINDOW *parent;
	uint width;
	uint height;
	uint x;
	uint y;
	byte sn;
{
	plistview_t list;
	list = ( plistview_t ) calloc ( 1 , sizeof ( listview_t ) );
	if ( list == NULL )
		return NULL;
	list->width = width;
	list->height = height;
	list->window = derwin ( parent , list->height , list->width , y , x );
	wbkgd ( list->window , COLOR_PAIR ( COLORS_LISTVIEW ) );
	wrefresh( parent );
	list->show_num = sn;
	return list;
}


byte
 listview_set_items ( list , max_items )
	plistview_t list;
	uint max_items;
{
	list->nwin = 0;
	list->nitems = max_items;
	list->citem = 0;
	list->sitem = 0;
	list->nrealloc = 1;
	list->highlight_item = 0;
	list->selected_item = LISTVIEW_NONE;
	if ( list->nwin > list->height )
		list->nwin = list->height;
	list->items = ( WINDOW ** ) calloc ( list->nitems+1 , sizeof ( WINDOW * ) );
	if ( list->items == NULL )
		return 0;
	list->attr = ( int * ) calloc ( list->nitems+1 , sizeof ( int ) );
	if ( (list->s_items = dstr_alloc ( list->nitems , MAX_FILE_NAME )) == NULL )
		return 0;
	return 1;
}


void
 listview_add_item ( list , str , attrib )
	plistview_t list;
	const char *str;
	int attrib;
{
	snprintf ( list->s_items[list->citem] , 256 , "%s" , str );
	list->attr[list->citem] = attrib;
	list->citem++;
	if ( list->nwin < list->height )
		list->nwin++;
	if (list->citem >= list->nitems-2 )
	{
		uint last = list->nitems;
		list->nrealloc++;
		list->nitems = list->nrealloc*list->nitems;
		list->items = (WINDOW **) realloc ( list->items , sizeof ( WINDOW * ) * (list->nitems+1) );
		list->attr = ( int * ) realloc ( list->attr , sizeof ( int ) * (list->nitems+1) );
		list->s_items = dstr_realloc ( list->s_items , last, list->nitems , MAX_FILE_NAME );
	}
}

void
 listview_remove_item ( list , idx )
	plistview_t list;
	uint idx;
{
	if ( list->citem > 0 )
		list->citem--;
	
	if ( list->nwin < list->height )
		list->nwin--;

	uint chk = list->nitems*(list->nrealloc-1);
	
	if ( list->citem <= chk )
	{
		uint last = list->nitems;
		list->nitems = chk;
		list->items = (WINDOW **) realloc ( list->items , sizeof ( WINDOW * ) * (list->nitems+1) );
		list->attr = ( int * ) realloc ( list->attr , sizeof ( int ) * ( list->nitems+1) );
		list->s_items = dstr_realloc ( list->s_items , last  , list->nitems , MAX_FILE_NAME );
	}
}

void
 listview_show ( list )
	plistview_t list;
{
	uint i;
	for ( i = 0 ; i < list->nwin ; i++ )
	{
		list->items[i] = derwin ( list->window , 1 , list->width  , i , 0 );
		if ( list->show_num )
			wprintw ( list->items[i] , "%d: %s" , list->sitem+i+1 , list->s_items[list->sitem+i] );
		else
			wprintw ( list->items[i] , " %s" , list->s_items[list->sitem+i] );
		wbkgd ( list->items[i] , COLOR_PAIR ( COLORS_LISTVIEW ) | list->attr[list->sitem+i] );
		wrefresh ( list->items[i] );
	}
	wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_HIGHLISTVIEW ) | list->attr[list->sitem+i] );
	redrawwin ( list->window );
	wrefresh ( list->window );
}

void
 listview_scroll ( list , direction )
	plistview_t list;
	byte direction;
{
	uint i;
	switch ( direction )
	{
		case LISTVIEW_UP:
			list->sitem--;
			for ( i = 0 ; i < list->nwin ; i++ )
			{
				werase ( list->items[i] );
				if ( list->show_num )
					wprintw ( list->items[i] , "%d: %s" , list->sitem+i+1 , list->s_items[list->sitem+i] );
				else
					wprintw ( list->items[i] , " %s" , list->s_items[list->sitem+i] );
				wbkgd ( list->items[i] , COLOR_PAIR ( COLORS_LISTVIEW ) | list->attr[list->sitem+i] );
				wnoutrefresh ( list->items[i] );
			}
			wbkgd ( list->items[0] , COLOR_PAIR ( COLORS_HIGHLISTVIEW ) | list->attr[list->sitem] );
			wnoutrefresh ( list->items[0] );
			break;
		
		case LISTVIEW_DOWN:
			list->sitem++;
			for ( i = 0 ; i < list->nwin ; i++ )
			{
				werase ( list->items[i] );
				if ( list->show_num )
					wprintw ( list->items[i] , "%d: %s" , list->sitem+i+1 , list->s_items[list->sitem+i] );
				else
					wprintw ( list->items[i] , " %s" , list->s_items[list->sitem+i] );
				wbkgd ( list->items[i] , COLOR_PAIR ( COLORS_LISTVIEW ) | list->attr[list->sitem+i] );
				wnoutrefresh ( list->items[i] );
			}
			wbkgd ( list->items[list->nwin-1] , COLOR_PAIR ( COLORS_HIGHLISTVIEW ) | list->attr[list->sitem+list->nwin-1] );
			wnoutrefresh ( list->items[list->nwin-1] );
			break;
	}
	wrefresh ( list->window );
}

void
 listview_next_item ( list )
	plistview_t list;
{
	if ( list->highlight_item+1 < list->nwin )
	{
		if ( list->highlight_item != list->selected_item )
		{
			wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_LISTVIEW ) | list->attr[list->sitem+list->highlight_item] );
			wnoutrefresh ( list->items[list->highlight_item] );
		}
		list->highlight_item++;
		if ( list->highlight_item == list->selected_item )
		{
			wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_HIGHSEL ) | list->attr[list->sitem+list->highlight_item] );
			wnoutrefresh ( list->items[list->highlight_item] );
		}
		else
		{
			if ( list->selected_item != LISTVIEW_NONE )
			{
				wbkgd ( list->items[list->selected_item] , COLOR_PAIR ( COLORS_SEL ) | list->attr[list->sitem+list->highlight_item] );
				wnoutrefresh ( list->items[list->selected_item] );
			}
			wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_HIGHLISTVIEW ) | list->attr[list->sitem+list->highlight_item] );
			wnoutrefresh ( list->items[list->highlight_item] );
		}
	}
	else
	{
		if ( list->citem-list->sitem > list->nwin )
			listview_scroll ( list , LISTVIEW_DOWN );
	}
	list->selected_item = LISTVIEW_NONE;
}


uint
 listview_select_item ( list )
	plistview_t list;
{
	if ( list->selected_item != LISTVIEW_NONE )
	{
		wbkgd ( list->items[list->selected_item] , COLOR_PAIR ( COLORS_LISTVIEW ) );
		wnoutrefresh ( list->items[list->selected_item] );
	}
	wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_HIGHSEL ) );
	wnoutrefresh ( list->items[list->highlight_item] );
	list->selected_item = list->highlight_item;
	return list->selected_item;
}

void
 listview_prev_item ( list )
	plistview_t list;
{
	if ( list->highlight_item > 0 )
	{
		if ( list->highlight_item != list->selected_item )
		{
			wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_LISTVIEW ) | list->attr[list->sitem+list->highlight_item] );	
			wnoutrefresh ( list->items[list->highlight_item] );
		}
		list->highlight_item--;
		if ( list->highlight_item == list->selected_item )
		{
			wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_HIGHSEL ) | list->attr[list->sitem+list->highlight_item] );
			wnoutrefresh ( list->items[list->highlight_item] );
		}
		else
		{
			if ( list->selected_item != LISTVIEW_NONE )
			{
				wbkgd ( list->items[list->selected_item] , COLOR_PAIR ( COLORS_SEL ) | list->attr[list->sitem+list->highlight_item] );
				wnoutrefresh ( list->items[list->selected_item] );
			}
			wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_HIGHLISTVIEW ) | list->attr[list->sitem+list->highlight_item] );
			wnoutrefresh ( list->items[list->highlight_item] );
		}
	}
	else
	{
		if ( list->sitem > 0 )
			listview_scroll ( list , LISTVIEW_UP );
	}
	list->selected_item = LISTVIEW_NONE;
}

/*
void
 listview_set_attr_item ( list )
	plistview_t list;
{ wattrset ( list->items[list->citem] , list->item_attr[list->citem] ); }
*/

WINDOW *
 listview_get_window ( list )
	plistview_t list;
{ return list->window; }

char *
 listview_get_highlight ( list )
	plistview_t list;
{ return list->s_items[list->sitem+list->highlight_item]; }


void
 listview_mvrs ( list , width , height , x , y )
/* listview_movenresize ( list , width , height , x , y ) */
	plistview_t list;
	uint width;
	uint height;
	uint x;
	uint y;
{
	int i;
	mvwin ( list->window , y , x );
	wresize ( list->window , height , width );
	refresh();
	for ( i = 0 ; i < list->nwin ; i++ )
		wresize ( list->items[i] , 1 , width );
	wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_HIGHLISTVIEW ) );
	wnoutrefresh ( list->items[list->highlight_item] );
}

void
 listview_focus ( list , st )
	plistview_t list;
	byte st;
{
	if ( st )
	{
		wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_HIGHLISTVIEW ) );
		wnoutrefresh ( list->items[list->highlight_item] );
	}
	else
	{
		wbkgd ( list->items[list->highlight_item] , COLOR_PAIR ( COLORS_DEFAULT ) );
		wnoutrefresh ( list->items[list->highlight_item] );
	}
}

void
 listview_clean ( list )
	plistview_t list;
{
	if ( list->nwin > 0 )
	{
		uint i;
		for ( i = 0 ; i < list->nwin ; i++ )
			delwin ( list->items[i] );
		wclrtobot ( list->window  );
		wrefresh ( list->window );
	}
	dstr_free ( list->s_items , list->nitems );
	free ( list->attr );
	free ( list->items );
}

void
 listview_destroy ( list )
	plistview_t list;
{
	delwin ( list->window );
	free ( list );
}

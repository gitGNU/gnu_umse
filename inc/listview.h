/*

    listview.h
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

#ifndef _LISTVIEW_H
#	define _LISTVIEW_H

	plistview_t listview_create ( uint width , uint height , uint x , uint y , byte show_num );
	plistview_t listview_create_child ( WINDOW * parent , uint width , uint height , uint x , uint y , byte show_num );
	
	byte listview_set_items ( plistview_t list , uint max_items );
	void listview_add_item ( plistview_t list , const char * str , int attrib );
	void listview_clean ( plistview_t list );
	
	void listview_show ( plistview_t list );
	void listview_refresh ( plistview_t list );
	
	void listview_next_item ( plistview_t list );
	void listview_prev_item ( plistview_t list );
	
	uint listview_select_item ( plistview_t list );
	
	WINDOW * listview_get_window ( plistview_t list );
	
	void listview_mvrs ( plistview_t list , uint width , uint height , uint x , uint y );
	
	void listview_focus ( plistview_t list , byte st );
	
	char * listview_get_highlight ( plistview_t list );
	
	void listview_destroy ( plistview_t list );

#endif

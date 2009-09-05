/*

    static.h
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

#ifndef _STATIC_H
#	define _STATIC_H
	
	WINDOW * static_window_create ( uint width , uint height , uint x , uint y  , const char * text , byte t_align , int t_color , byte boxwin );
	WINDOW * static_window_create_child ( WINDOW * parent , uint width , uint height , uint x , uint y  , const char * text , byte t_align , int t_color , byte boxwin );
	void static_update ( WINDOW * swin );
	void static_set ( WINDOW *swin , char *str );
	void static_redraw ( WINDOW *swin );
	void static_window_destroy ( WINDOW * swin );
	

#endif

/*

    browse.c
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
 browse_set ( input , list , curr_path )
	pinput_t input;
	plistview_t list;
	char * curr_path;
{
	struct dirent **dirlist;
	int nf = 0, i = 0;

	listview_clean ( list );
	listview_set_items ( list , ALLOC_MEM );
	
	nf = scandir ( curr_path , &dirlist , 0 , alphasort );
	
	for ( i = 0; i < nf ; i++ )
	{
		if ( dirlist[i]->d_type == DT_DIR )
			listview_add_item ( list , dirlist[i]->d_name , A_BOLD );
		else
		{
			if ( strchr ( dirlist[i]->d_name , '.' ) != NULL )
			{
				char *ext = strchr ( dirlist[i]->d_name , '.' )+1;
				if ( is_supported ( input , ext ) != -1 )
					listview_add_item ( list , dirlist[i]->d_name , A_NORMAL );
			}
		}
		free ( dirlist[i] );
	}

	free ( dirlist );
	listview_show ( list );
}

/*

    file.c
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

byte
 is_dir ( path )
	char * path;
{
	struct stat status;
	if ( stat ( path , &status ) == -1 )
		return 0;
	if ( S_ISDIR ( status.st_mode ) )
		return 1;
	return 0;
}

byte
 copen ( path )
	char * path;
{
	DIR *dir;
	dir = opendir ( path );
	if ( !dir )
		return 0;
	closedir ( dir );
	return 1;
}

void
 set_prev_directory ( path )
	char *path;
{
	unsigned int l = strlen ( path );
	path+=l;
	while ( l > 1 )
	{
		if ( *path == '/' )
			break;
		path--;
		l--;
	}
	*path=0;
}

uint
 nfiles ( path , ext )
 	char *path;
	char *ext;
{
	DIR *dir; struct dirent *dread;
	uint ret = 0; char *fext;

	dir = opendir ( path );
	if ( dir == NULL )
		return 0;
	
	while ( (dread = readdir ( dir ) ) != NULL )
	{
		if ( ext == NULL )
		{
			ret++;
		}
		else
		{
			fext = strchr ( dread->d_name , '.' );
			if ( fext == NULL )
				continue;
			if ( !strcmp ( ext , fext ) )
				ret++;
		}
	}

	closedir ( dir );

	return ret;
}


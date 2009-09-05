/*

    str.c
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

char **
 dstr_alloc ( d_one , d_two )
	uint d_one;
	uint d_two;
{
	char **ptr = NULL;
	uint i;
	if ( (ptr = ( char ** ) calloc ( d_one+1 , sizeof ( char* ) )) == NULL )
		return NULL;
	for ( i = 0 ; i <= d_one ; i++ )
	{
		if ( ( ptr[i] = ( char * ) calloc ( d_two , sizeof ( char ) ) ) == NULL )
			break;
	}
	return ptr;
}

char **
 dstr_realloc ( ptr , d_last , d_one , d_two )
	char **ptr;
	uint d_last;
	uint d_one;
	uint d_two;
{
	uint i;
	if ( (ptr = ( char ** ) realloc ( ptr , (d_one+1) * sizeof ( char* ) )) == NULL )
		return NULL;

	for ( i = d_last+1 ; i <= d_one ; i++ )
	{
		if ( ( ptr[i] = ( char * ) calloc ( d_two , sizeof ( char ) ) ) == NULL )
			break;
	}
	return ptr;
}

void
 dstr_free ( ptr , d_one )
	char **ptr;
	uint d_one;
{
	uint i;
	for ( i = 0 ; i <= d_one ; i++ )
		free ( ptr[i] );
	free ( ptr );
}

uint
 getnchar ( source , c )
	char * source;
	char c;
{
	uint ret = 0;
	while ( *source )
	{
		if ( *source == c )
			ret++;
		source++;
	}
	return ret;
}

uint
 strbrkidx ( str1 , chr , idx )
 	char *str1;
	char chr;
	uint idx;
{
	uint cidx = 0 , pos = 0;
	while ( *str1 )
	{
		if ( cidx == idx )
			return pos;
		if ( *str1 == chr )
			cidx++;
		str1++; pos++;
	}
	return ~0;
}

byte
 splitstr ( str1 , str2 , str2_size , delim , start )
	char * str1;
	char * str2;
	uint str2_size;
	char delim;
	uint start;
{
	uint size = 0;
	str1 += start;
	while ( *str1 )
	{
		if ( size > str2_size )
			break;
		if ( *str1 == delim )
			break;
		*str2++ = *str1++;
		size++;
	}
	*str2 = 0;
	return 0;
}


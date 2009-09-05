/*

    output.h
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

#ifndef _OUTPUT_H
#	define _OUTPUT_H

	poutput_t output_create ( void );
	void output_initialize ( poutput_t output , int bits , int rate , int channels , int byte_format );
	void output_write ( poutput_t output , char * buffer , uint buffer_size );
	void output_close ( poutput_t output );
	void output_free ( poutput_t output );

#endif


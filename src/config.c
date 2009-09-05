/*

    config.c
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
 set_default_config ( theme )
	ptheme_t theme;
{
	theme->titlebar_fore = COLOR_WHITE;
	theme->titlebar_bkgd = COLOR_BLUE;
	
	theme->listview_fore = COLOR_WHITE;
	theme->listview_bkgd = -1;
	
	theme->highlistview_fore = COLOR_WHITE;
	theme->highlistview_bkgd = COLOR_BLUE;
	
	theme->sel_fore = COLOR_RED;
	theme->sel_bkgd = -1;
	
	theme->highsel_fore = COLOR_RED;
	theme->highsel_bkgd = COLOR_BLUE;
	
	theme->default_fore = COLOR_WHITE;
	theme->default_bkgd = -1;

	theme->desc_fore = COLOR_BLACK;
	theme->desc_bkgd = COLOR_WHITE;
}

void
 free_pwd ( pass )
 	struct passwd * pass;
{
	if ( pass->pw_name != NULL ) free ( pass->pw_name );
	if ( pass->pw_passwd != NULL ) free ( pass->pw_passwd );
	if ( pass->pw_gecos != NULL ) free ( pass->pw_gecos );
	if ( pass->pw_dir != NULL ) free ( pass->pw_dir );
	if ( pass->pw_shell != NULL ) free ( pass->pw_shell );
	
	pass->pw_name = NULL;
	pass->pw_passwd = NULL;
	pass->pw_gecos = NULL;
	pass->pw_dir = NULL;
	pass->pw_shell = NULL;
}

pconfig_t
 create_config ( void )
{
	pconfig_t conf = NULL;
	char *h;
	conf = ( pconfig_t ) calloc ( 1 , sizeof ( config_t ) );
	if ( conf == NULL )
		return NULL;
	h = getenv("HOME");
	snprintf ( conf->p_home , sizeof (conf->p_home) , "%s" , h );
	snprintf ( conf->p_plugins , sizeof (conf->p_plugins) , "%s/.umse/plugins" , conf->p_home );
	snprintf ( conf->p_logo , sizeof (conf->p_logo) , "%s/.umse/logo.asc" , conf->p_home );
	//free ( h );
	return conf;
}

void
 destroy_config ( config )
	pconfig_t config;
{
	free ( config );
}

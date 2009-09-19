/*

    umse.c
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

int
 main ( argc , argv )
	int argc;
	char **argv;
{
	WINDOW *wtitlebar, *wabout, *wdescription, *workspace_default;
	plistview_t default_browse, browse, default_playlist , playlist;
	pinput_t input_plugins; poutput_t output;
	byte quit = 0, current_workspace = WORKSPACE_DEFAULT; 
	theme_t theme; pconfig_t config;
	int key; byte focused = 0;
	PANEL *panel[NWORKSPACE], *top;
	char curr_path[FILENAME_MAX], s_tmp[FILENAME_MAX];
	
	set_default_config ( &theme );
	
	screen_init ();
	screen_colors ( &theme );
	
	config = create_config ( );
	
	#ifdef NAGSCREEN
		nagscreen ( config->p_logo );
	#endif

	output = output_create ();

	input_plugins = input_plugin_create ( config->p_home );
	input_plugin_init ( input_plugins );
	
	workspace_default = newwin ( stdscr->_maxy-2 , stdscr->_maxx+1 , 1 , 0 );
	wbkgd ( workspace_default , COLOR_PAIR ( COLORS_DEFAULT ) );
	mvwvline ( workspace_default , 0 , stdscr->_maxx/2 , ACS_VLINE , stdscr->_maxy-2 );
	
	wdescription = static_window_create ( stdscr->_maxx+1 , 1 , 0 , stdscr->_maxy-1 , "None." , STATIC_NORMAL , COLORS_DESC , false );
	
	wtitlebar = static_window_create ( stdscr->_maxx+1 , 1 , 0 , 0 , " "_RVERSION_ , STATIC_NORMAL , COLORS_TITLEBAR , false );
		
	wabout = static_window_create ( stdscr->_maxx+1 , stdscr->_maxy-2 , 0 , 1 , _ABOUT_ , STATIC_CENTER , COLORS_DEFAULT , true );
	
	default_browse = listview_create_child ( workspace_default , (stdscr->_maxx-1)/2 , stdscr->_maxy-2 , 0 , 0 , false );
	default_playlist = listview_create_child ( workspace_default , (stdscr->_maxx-2)/2 , stdscr->_maxy-2 , ((stdscr->_maxx-1)/2)+1  , 0 , true );

	browse = listview_create ( stdscr->_maxx+1 , stdscr->_maxy-2 , 0 , 1 , false );
	playlist = listview_create ( stdscr->_maxx+1 , stdscr->_maxy-2 , 0 , 1 , true );
	
	panel[0] = new_panel ( workspace_default );
	panel[1] = new_panel ( browse->window );
	panel[2] = new_panel ( playlist->window );
	panel[3] = new_panel ( wabout );
	
	set_panel_userptr ( panel[0] , panel[1] );
	set_panel_userptr ( panel[1] , panel[2] );
	set_panel_userptr ( panel[2] , panel[3] );
	set_panel_userptr ( panel[3] , panel[0] );
	
	listview_set_items ( default_playlist , ALLOC_MEM );
	listview_set_items ( playlist , ALLOC_MEM );
	listview_set_items ( default_browse , ALLOC_MEM );
	listview_set_items ( browse , ALLOC_MEM );
	
	snprintf ( curr_path , sizeof ( curr_path ) , "%s" , config->p_home );
	
	browse_set ( input_plugins , default_browse , curr_path );
	browse_set ( input_plugins , browse , curr_path );
	
	listview_add_item ( browse , "None" , A_NORMAL );
	
	listview_add_item ( playlist , "None" , A_NORMAL );
	listview_add_item ( default_playlist , "None" , A_BOLD );
	
	listview_show ( default_browse );
	listview_show ( browse );
	listview_show ( default_playlist );
	listview_show ( playlist );
	
	listview_focus ( default_browse , true );
	listview_focus ( default_playlist , false );
	
	top = panel[0];
	
	hide_panel ( panel[1] );
	hide_panel ( panel[2] );
	hide_panel ( panel[3] );
	
	update_panels();
	doupdate();
	
	static_update ( wtitlebar );
	static_update ( wdescription );
	
	while ( !quit )
	{
		key = getch ( );
		switch ( key )
		{
			case CTRL('n'):
				hide_panel ( top );
				if ( current_workspace == WORKSPACE_ABOUT )
					current_workspace = WORKSPACE_DEFAULT;
				else
					current_workspace++;
				switch ( current_workspace )
				{
					case WORKSPACE_DEFAULT:
						browse_set ( input_plugins , default_browse , curr_path );
						default_browse->highlight_item = browse->highlight_item;
						default_browse->sitem = browse->sitem;
						listview_refresh ( default_browse );
						if ( focused )
						{
							listview_focus ( default_browse , false );
							listview_focus ( default_playlist , true );
						}
						else
						{
							listview_focus ( default_browse , true );
							listview_focus ( default_playlist , false );
						}
						break;
					
					case WORKSPACE_BROWSE:
						browse_set ( input_plugins , browse , curr_path );
						browse->sitem = default_browse->sitem;
						browse->highlight_item = default_browse->highlight_item;
						listview_refresh ( browse );
						break;
					
					case WORKSPACE_PLAYLIST:
						break;
					
					case WORKSPACE_ABOUT:
						break;
				}
				top = (PANEL * ) panel_userptr ( top );
				top_panel ( top );
				break;
				
			
			case KEY_TAB:
				if ( current_workspace == WORKSPACE_DEFAULT )
				{
					if ( !focused )
					{
						listview_focus ( default_browse , false );
						listview_focus ( default_playlist , true );
						focused = 1;
					}
					else
					{
						listview_focus ( default_browse , true );
						listview_focus ( default_playlist , false );
						focused = 0;
					}
				}
				break;
			
			
			case 'a':
				break;
				
			case KEY_UP:
				switch ( current_workspace )
				{
					case WORKSPACE_DEFAULT:
						if ( !focused )
							listview_prev_item ( default_browse );
						else
							listview_prev_item ( default_playlist );
						break;
						
					case WORKSPACE_BROWSE:
						listview_prev_item ( browse );
						break;
				}
				break;
				
			case KEY_DOWN:
				switch ( current_workspace )
				{
					case WORKSPACE_DEFAULT:
						if ( !focused )
							listview_next_item ( default_browse );
						else
							listview_next_item ( default_playlist );
						break;
						
					case WORKSPACE_BROWSE:
						listview_next_item ( browse );
						break;
				}
				break;
				
			case KEY_RETURN:
				switch ( current_workspace )
				{
					
					case WORKSPACE_DEFAULT:
					{
					
						char *curritem = listview_get_highlight ( default_browse );
						if ( !strcmp ( curritem , ".." ) )
						{
							set_prev_directory ( curr_path );
							browse_set ( input_plugins , default_browse , curr_path );
						}
						else if ( strcmp ( curritem , "." ) )
						{
							snprintf ( s_tmp , sizeof ( s_tmp ) , "%s/%s" , curr_path , curritem );
							if ( is_dir ( s_tmp ) )
							{
								if ( copen ( s_tmp ) )
								{
									snprintf ( curr_path , sizeof ( curr_path ) , "%s" , s_tmp );
									browse_set ( input_plugins ,  default_browse , curr_path );
								}
								else
									popup ( "Error!" , "Can't read this directory.\n" );
							}
							else
							{
								if ( !input_plugin_play ( output , input_plugins , s_tmp , wdescription ) )
								{
									popup ( "Error!" , "Can't read this file!" );
									input_plugin_stop ( output , input_plugins );
								}
							}
						}
					}
					break;
					
					case WORKSPACE_BROWSE:
					{
					
						char *curritem = listview_get_highlight ( browse );
						if ( !strcmp ( curritem , ".." ) )
						{
							set_prev_directory ( curr_path );
							browse_set ( input_plugins , browse , curr_path );
						}
						else if ( strcmp ( curritem , "." ) )
						{
							snprintf ( s_tmp , sizeof ( s_tmp ) , "%s/%s" , curr_path , curritem );
							if ( is_dir ( s_tmp ) )
							{
								if ( copen ( s_tmp ) )
								{
									snprintf ( curr_path , sizeof ( curr_path ) , "%s" , s_tmp );
									browse_set ( input_plugins , browse , curr_path );
								}
								else
									popup ( "Error!" , "Can't read this directory.\n" );
							}
							else
							{
								if ( !input_plugin_play ( output , input_plugins , s_tmp , wdescription ) )
								{
									popup ( "Error!" , "Can't read this file!" );
									input_plugin_stop ( output , input_plugins );
								}
							}
						}
					}
					break;
				}
				break;

			case KEY_LEFT:
				if ( input_plugin_playing ( input_plugins ) )
					input_plugin_ptrack ( input_plugins , wdescription );
				break;

			case KEY_RIGHT:
				if ( input_plugin_playing ( input_plugins ) )
					input_plugin_ntrack ( input_plugins , wdescription );
				break;
			
			case 's':
			case 'S':
				input_plugin_stop ( output , input_plugins );
				static_set ( wdescription , "Stop" );
				break;
			
			case 'q':
			case 'Q':
				quit = 1;
				break;
		}
		static_redraw ( wtitlebar );
		static_redraw ( wdescription );
		update_panels ();
		refresh();
	}
	
	listview_clean ( default_browse );
	listview_destroy ( default_browse );
	
	listview_clean ( default_playlist );
	listview_destroy ( default_playlist );

	delwin ( workspace_default );
	
	listview_clean ( browse );
	listview_destroy ( browse );
	
	listview_clean ( playlist );
	listview_destroy ( playlist );
	
	static_window_destroy ( wtitlebar );
	static_window_destroy ( wdescription );
	static_window_destroy ( wabout );
	
	del_panel ( panel[0] );
	del_panel ( panel[1] );
	del_panel ( panel[2] );
	del_panel ( panel[3] );

	input_plugin_stop ( output , input_plugins );	
	input_plugin_destroy ( input_plugins );

	output_free ( output );

	destroy_config ( config );
	
	screen_destroy ();
	
	return 0;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_systems.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:27:23 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/08 16:05:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_SYSTEMS_H
# define MENU_SYSTEMS_H

typedef	struct	s_menu
{
	Uint32		*menu_buffer;
	char		**map_names;
	char		*chosen_map;
	int			nbr_of_maps;
	int			selected;
	int			option;
	int			end;
	int			start;
}				t_menu;

void	load_map_names(t_menu *menu);
void	setup_game_loop(char **mapname, t_home *home, t_player *plr, int *menu_option);
void	setup_editor(t_home *home);
void	setup_menu(t_menu *menu, int *game_state);
void	process_inputs_load_menu(int *game_state, SDL_Event *e, t_menu *menu);
void	process_inputs_main_menu(int *game_state, SDL_Event *e, int *option);
void	launch_load_menu_loop(t_menu *menu, t_window *win, SDL_Event *e, int *game_state);
void	launch_game_loop(t_home *home, t_player *plr, t_frame *frame, SDL_Event *e);
void	update_main_menu(Uint32 *menu_buffer, int option);

/*
** Menu utility functions
*/

int		get_map_count(int *count, DIR **dir, struct dirent **dir_entry);
void	loop_map_names(char **map_names, struct dirent *dir_entry, DIR *dir);
void	update_load_menu(t_menu *menu, int sym);
void	get_menu_range_key_up(t_menu *menu);
void	get_menu_range_key_down(t_menu *menu);
void	free_game_assets(t_home *home);
void	update_option_load_menu(int *game_state, t_menu *menu, int sym);
void	update_option_main_menu(int *game_state, int sym, int *option);
int		get_game_state(int *option);

#endif

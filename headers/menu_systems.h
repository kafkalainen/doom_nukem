/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_systems.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:27:23 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/12 13:49:47 by rzukale          ###   ########.fr       */
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
}				t_menu;

void	get_map_count(int *count, DIR **dir, struct dirent **dir_entry);
void	load_map_names(t_menu *menu);
void	setup_game_loop(char **mapname, t_home *home, t_player *plr);
void	setup_editor(t_home *home);
void	process_inputs_load_menu(int *game_state, SDL_Event *e, t_menu *menu);
void	process_inputs_main_menu(int *game_state, SDL_Event *e, int *option);
void	launch_load_menu_loop(t_menu *menu, t_window *win, SDL_Event *e, int *game_state);
void	launch_game_loop(t_home *home, t_player *plr, t_frame *frame, SDL_Event *e);

#endif

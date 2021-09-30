/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_systems.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:27:23 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/29 18:43:43 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_SYSTEMS_H
# define MENU_SYSTEMS_H

typedef struct s_menu
{
	t_buffer	buffer;
	char		*chosen_map;
	char		**map_names;
	int			nbr_of_maps;
	int			selected;
	int			option;
	int			end;
	int			start;
}				t_menu;

void	load_map_names(char ***map_names, int *nbr_of_maps);
void	setup_game_loop(t_home *home, t_player *plr, int *menu_option);
void	setup_menu(t_menu *menu, int *game_state);
void	process_inputs_load_menu(int *game_state, SDL_Event *e, t_menu *menu);
void	process_inputs_main_menu(int *game_state, SDL_Event *e, int *option);
void	launch_load_menu_loop(t_menu *menu, t_home *home, SDL_Event *e);
void	launch_settings_menu(t_menu *menu, t_home *home, SDL_Event *e);
void	launch_game_loop(t_home *home, t_player *plr,
			t_frame *frame, SDL_Event *e);
void	update_main_menu(t_buffer *buffer, int *option);

/*
** Menu utility functions
*/

int		get_map_count(int *count, DIR **dir, struct dirent **dir_entry);
void	loop_map_names(char **map_names, struct dirent *dir_entry, DIR *dir);
void	update_load_menu(t_menu *menu, int sym);
void	get_menu_range_key_up(int *option, int *start,
			int *end, int nbr_of_maps);
void	get_menu_range_key_down(int *option, int *start,
			int *end, int nbr_of_maps);
void	free_game_assets(t_home *home, t_audio *audio);
void	update_option_load_menu(int *game_state, t_menu *menu, int sym);
void	update_option_main_menu(int *game_state, int sym, int *option);
int		get_game_state(int *option);
Uint32	get_color(enum e_colour color);

#endif

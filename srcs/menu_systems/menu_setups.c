/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_setups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:17:34 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/21 09:35:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_map_count(int *count, DIR **dir, struct dirent **dir_entry)
{
	char	*found;

	*dir_entry = readdir(*dir);
	while (*dir_entry != NULL)
	{
		found = ft_strstr((*dir_entry)->d_name, ".DN");
		if (found != NULL)
			(*count)++;
		*dir_entry = readdir(*dir);
	}
	rewinddir(*dir);
	if ((*count) == 0)
	{
		closedir(*dir);
		return (-1);
	}
	return (1);
}

void	load_map_names(char ***map_names, int *nbr_of_maps)
{
	DIR				*dir;
	struct dirent	*dir_entry;

	dir = opendir("map_files/");
	if (dir == NULL)
		error_output("Failed to open map_files directory.\n");
	if (get_map_count(nbr_of_maps, &dir, &dir_entry) == -1)
		return ;
	*map_names = (char **)malloc(sizeof(char *) * (*nbr_of_maps));
	if (!map_names)
		error_output("Failed to allocate memory to map file names.\n");
	dir_entry = readdir(dir);
	loop_map_names(*map_names, dir_entry, dir);
	closedir(dir);
}

void	setup_menu(t_menu *menu, int *game_state)
{
	menu->nbr_of_maps = 0;
	menu->buffer.pxl_buffer = (Uint32 *)malloc(sizeof(Uint32)
			* (SCREEN_WIDTH * SCREEN_HEIGHT));
	if (!menu->buffer.pxl_buffer)
		error_output("Failed to allocate memory to menu buffer\n");
	menu->option = 0;
	menu->buffer.width = SCREEN_WIDTH;
	menu->buffer.height = SCREEN_HEIGHT;
	*game_state = MAIN_MENU;
}

void	setup_game_loop(t_home *home, t_player *plr, int *menu_option)
{
	ft_putstr("You chose: ");
	ft_putendl_fd(home->map, 1);
	initialize_player(plr);
	if (initialize_hud(&plr->hud))
		error_output("Memalloc failed for HUD.");
	if (load_map_file(plr, home))
		error_output("Error while loading map!");
	if (initialize_skybox(&home->skybox, home->sectors, home->nbr_of_sectors))
		error_output("Memory allocation failed for skybox.");
	if (setup_fps(&home->t))
		error_output("Memory allocation failed!");
	if (load_game_audio(&plr->audio))
		error_output("Loading game audio failed!");
	initialize_cutscene(home->sectors[plr->start_sector], plr, start_cutscene);
	toggle_music(plr->audio.music);
	*menu_option = 0;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	plr->input.mouse = 1;
	home->game_state = GAME_LOOP;
}

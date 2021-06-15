/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_setups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:17:34 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/15 14:37:27 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_map_count(int *count, DIR **dir, struct dirent **dir_entry)
{
	char	*found;

	*dir_entry = readdir(*dir);
	while (*dir_entry != NULL)
	{
		found = ft_strstr((*dir_entry)->d_name, ".TEST");
		if (found != NULL)
			(*count)++;
		*dir_entry = readdir(*dir);
	}
	rewinddir(*dir);
	if ((*count) == 0)
	{
		printf("no maps to load\n");
		closedir(*dir);
		return (-1);
	}
	return (1);
}

void	load_map_names(t_menu *menu)
{
	DIR				*dir;
	struct dirent	*dir_entry;

	dir = opendir("map_files/");
	if (dir == NULL)
		error_output("Failed to open map_files directory.\n");
	if (get_map_count(&menu->nbr_of_maps, &dir, &dir_entry) == -1)
		return ;
	menu->map_names = (char **)malloc(sizeof(char *) * (menu->nbr_of_maps));
	if (!menu->map_names)
		error_output("Failed to allocate memory to map file names.\n");
	dir_entry = readdir(dir);
	loop_map_names(menu->map_names, dir_entry, dir);
	closedir(dir);
}

void	setup_menu(t_menu *menu, int *game_state)
{
	menu->nbr_of_maps = 0;
	menu->menu_buffer = (Uint32 *)malloc(sizeof(Uint32)
			* (SCREEN_WIDTH * SCREEN_HEIGHT));
	if (!menu->menu_buffer)
		error_output("Failed to allocate memory to menu_buffer\n");
	menu->option = 0;
	*game_state = MAIN_MENU;
}

void	print_walls(t_wall *walls)
{
	t_wall	*tmp;

	tmp = walls;
	while (tmp != NULL)
	{
		printf("wall facing: %f\n", tmp->wall_facing);
		tmp = tmp->next;
	}
	printf("leaving print walls\n");
}

void	print_sectors(t_home *home)
{
	unsigned int i;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		printf("Sector %i\n", i);
		printf("sector index: %i\n", home->sectors[i]->idx_sector);
		printf("tex_floor: %i\n", home->sectors[i]->tex_floor);
		printf("tex_ceil: %i\n", home->sectors[i]->tex_ceil);
		printf("nb_of_ceil: %i\n", home->sectors[i]->nb_of_ceil);
		printf("nb_of_ground: %i\n", home->sectors[i]->nb_of_ground);
		printf("nb_of_walls: %i\n", home->sectors[i]->nb_of_walls);
		// loop linked list
		// print_walls(home->sectors[i]->walls);
		i++;
	}
}

void	setup_game_loop(char **mapname, t_home *home,
	t_player *plr, int *menu_option)
{
	ft_putstr("You chose: ");
	ft_putendl_fd(*mapname, 1);
	init_player(plr);
	if (initialize_skybox(&home->skybox))
		error_output("Memory allocation failed!\n");
	if (load_map_file(home, *mapname))
		exit(EXIT_FAILURE);
	// if (open_file(home, "map_files/test.DATA") < 0)
	// 		error_output("Could not successfully open map file.");
	init_textures(home);
	print_sectors(home);
	// ret = load_game_audio(&plr->audio);
	// if (ret)
	// {
	// 	cleanup_audio(&plr->audio);
	// 	SDL_Quit();
	// 	clean_up(home);
	// }
	// if (Mix_PlayingMusic() == 0)
	// 	Mix_PlayMusic(plr->audio.music, -1);
	if (setup_fps(&home->t))
		error_output("Memory allocation failed!\n");
	ft_strdel(mapname);
	*mapname = NULL;
	*menu_option = 0;
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void	setup_editor(t_home *home)
{
	init_textures(home);
}

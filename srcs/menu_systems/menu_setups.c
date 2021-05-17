/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_setups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:17:34 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/17 10:27:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	get_map_count(int *count, DIR **dir, struct dirent **dir_entry)
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
}

void	load_map_names(t_menu *menu)
{
	DIR				*dir;
	struct dirent	*dir_entry;
	char			*found;
	int				i;

	dir = opendir("map_files/");
	if (dir == NULL)
		error_output("Failed to open map_files directory.\n"); // redesign this to return to main menu instead of quitting?
	get_map_count(&menu->nbr_of_maps, &dir, &dir_entry);
	if (menu->nbr_of_maps == 0)
	{
		printf("no maps to load\n");
		return ;
	}
	menu->map_names = (char **)malloc(sizeof(char *) * menu->nbr_of_maps);
	if (!menu->map_names)
		error_output("Failed to allocate memory to map file names.\n");
	dir_entry = readdir(dir);
	i = 0;
	while (dir_entry != NULL)
	{
		found = ft_strstr(dir_entry->d_name, ".TEST");
		if (found != NULL)
		{
			menu->map_names[i] = (char *)malloc(sizeof(char) * (ft_strlen((const char *)dir_entry->d_name) + 1));
			if (!menu->map_names[i])
				error_output("Failed to allocate memory to map file name.\n");
			menu->map_names[i] = ft_strcpy(menu->map_names[i], (const char *)dir_entry->d_name);
			i++;
		}
		dir_entry = readdir(dir);
	}
	closedir(dir);
}

void	setup_menu(t_menu *menu, int *game_state)
{
	menu->nbr_of_maps = 0;
	menu->menu_buffer = (Uint32 *)malloc(sizeof(Uint32) * (SCREEN_WIDTH * SCREEN_HEIGHT));
	if (!menu->menu_buffer)
		error_output("Failed to allocate memory to menu_buffer\n");
	menu->option = 0;
	*game_state = MAIN_MENU;
}

void	setup_game_loop(char **mapname, t_home *home, t_player *plr)
{
	// int ret;
	plr = plr;
	ft_putstr("You chose: ");
	ft_putendl_fd(*mapname, 1);
	if (load_map_file(home, *mapname))
		exit(EXIT_FAILURE);
	// if (open_file(home, "map_files/test.DATA") < 0)
	// 		error_output("Could not successfully open map file.");
	init_textures(home);
	// ret = load_game_audio(&plr->audio);
	// if (ret)
	// {
	// 	cleanup_audio(&plr->audio);
	// 	SDL_Quit();
	// 	clean_up(home);
	// }
	// if (Mix_PlayingMusic() == 0)
	// 	Mix_PlayMusic(plr->audio.music, -1);
	ft_strdel(mapname);
	*mapname = NULL;
}

void	setup_editor(t_home *home)
{
	init_textures(home);
}

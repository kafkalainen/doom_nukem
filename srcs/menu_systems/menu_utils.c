/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:18:54 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/03 16:32:05 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// REVISIT ADD STORY STRING MANAGEMENT
// free_story(&home->story);
void	free_game_assets(t_home *home)
{
	if (home->t.frame_times)
		free(home->t.frame_times);
	free_sectors(home);
	free_all_textures(home->textures, &home->nbr_of_textures);
	free_entities(home);
	free_projectiles(home);
}

void	get_menu_range_key_down(t_menu *menu)
{
	if (menu->option == 0)
	{
		menu->start = 0;
		if ((menu->nbr_of_maps - 8) > 0)
			menu->end = 7;
		else
			menu->end = menu->nbr_of_maps - 1;
	}
	if (menu->option > menu->end)
		menu->end = menu->option;
	if ((menu->end - 7) > 0)
		menu->start = (menu->end - 7);
	else
		menu->start = 0;
}

void	get_menu_range_key_up(t_menu *menu)
{
	if (menu->option == menu->nbr_of_maps - 1)
	{
		menu->end = menu->option;
		if ((menu->option - 7) > 0)
			menu->start = (menu->option - 7);
		else
			menu->start = 0;
	}
	if (menu->option < menu->start)
		menu->start = menu->option;
	if ((menu->start + 7) > menu->nbr_of_maps - 1)
		menu->end = menu->nbr_of_maps - 1;
	else
		menu->end = (menu->start + 7);
}

void	update_load_menu(t_menu *menu, int sym)
{
	int				y;
	int				i;
	t_plx_modifier	mod;

	if (sym == SDLK_DOWN)
		get_menu_range_key_down(menu);
	else if (sym == SDLK_UP)
		get_menu_range_key_up(menu);
	i = menu->start;
	y = 0;
	mod.colour = 0;
	mod.size = TEXT_SIZE;
	mod.len = 100;
	while (i <= menu->end)
	{
		if (i == menu->option)
			mod.colour = get_color(red);
		else
			mod.colour = get_color(white);
		ft_str_pxl(menu->menu_buffer,
			(t_xy){(SCREEN_WIDTH * 0.5) - 200, 25 + y},
			menu->map_names[i], mod);
		y += 15;
		i++;
	}
}

void	loop_map_names(char **map_names, struct dirent *dir_entry, DIR *dir)
{
	char	*found;
	int		i;

	i = 0;
	while (dir_entry != NULL)
	{
		found = ft_strstr(dir_entry->d_name, ".TEST");
		if (found != NULL)
		{
			map_names[i] = (char *)malloc(sizeof(char)
					* (ft_strlen((const char *)dir_entry->d_name) + 1));
			if (!map_names[i])
				error_output("Failed to allocate memory to map file name.\n");
			map_names[i] = ft_strcpy(map_names[i],
					(const char *)dir_entry->d_name);
			i++;
		}
		dir_entry = readdir(dir);
	}
}

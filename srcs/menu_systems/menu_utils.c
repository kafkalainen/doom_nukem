/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:18:54 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/20 11:51:21 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	return_to_main_from_game(t_home *home, t_player *plr)
{
	free_sectors(home);
	free_all_textures(home->editor_tex, &home->nbr_of_textures);
	init_player(plr);
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
	while (i <= menu->end)
	{
		if (i == menu->option)
			mod.colour = red;
		else
			mod.colour = white;
		str_pxl(menu->menu_screen.buffer, (t_xy){(SCREEN_WIDTH * 0.5) - 200, 25 + y},
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

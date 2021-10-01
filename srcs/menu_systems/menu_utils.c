/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:18:54 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/01 16:51:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	get_menu_range_key_down(int *option, int *start,
	int *end, int nbr_of_maps)
{
	if (*option == 0)
	{
		*start = 0;
		if ((nbr_of_maps - 8) > 0)
			*end = 7;
		else
			*end = nbr_of_maps - 1;
	}
	if (*option > *end)
		*end = *option;
	if ((*end - 7) > 0)
		*start = (*end - 7);
	else
		*start = 0;
}

void	get_menu_range_key_up(int *option, int *start,
	int *end, int nbr_of_maps)
{
	if (*option == nbr_of_maps - 1)
	{
		*end = *option;
		if ((*option - 7) > 0)
			*start = (*option - 7);
		else
			*start = 0;
	}
	if (*option < *start)
		*start = *option;
	if ((*start + 7) > nbr_of_maps - 1)
		*end = nbr_of_maps - 1;
	else
		*end = (*start + 7);
}

static Uint32	get_menu_color(int i, int option)
{
	if (i == option)
		return (0xFFFFCC00);
	return (get_color(white));
}

void	update_load_menu(t_menu *menu, int sym)
{
	t_xy			coord;
	int				i;
	t_plx_modifier	mod;

	if (sym == SDLK_DOWN)
		get_menu_range_key_down(&menu->option, &menu->start,
			&menu->end, menu->nbr_of_maps);
	else if (sym == SDLK_UP)
		get_menu_range_key_up(&menu->option, &menu->start,
			&menu->end, menu->nbr_of_maps);
	i = menu->start;
	coord = vec2(0, SCREEN_HEIGHT * 0.5f - 45);
	mod.colour = 0;
	mod.size = TEXT_SIZE;
	while (i <= menu->end)
	{
		mod.colour = get_menu_color(i, menu->option);
		mod.len = ft_strlen(menu->map_names[i]);
		coord.x = center_text_x_axis(0, SCREEN_WIDTH, mod.size, mod.len);
		ft_str_pxl(&menu->buffer, coord, menu->map_names[i], mod);
		coord.y += 15;
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
		found = ft_strstr(dir_entry->d_name, ".DN");
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

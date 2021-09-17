/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text_and_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:03:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/17 09:29:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_help_text_two(t_action *action, t_buffer *buffer)
{
	if (action->create_sector == user_input)
	{
		show_user_help("Create at least three points to create a sector.",
			buffer, 0, get_color(orange));
		show_user_help("Sector has to be a convex polygon.",
			buffer, 1, get_color(orange));
		show_user_help("Left click creates a point, right deletes last point.",
			buffer, 2, get_color(orange));
		show_user_help("Last point must close sector.",
			buffer, 3, get_color(orange));
	}
	if (action->create_entity == allocate)
	{
		show_user_help(
			"Click a point in a selected sector to create an entity.",
			buffer, 0, get_color(orange));
	}
}

void	draw_help_text(t_action *action, t_buffer *buffer)
{
	if (action->convert_to_portal)
	{
		show_user_help("Use Mouse left click to select the sector",
			buffer, 0, get_color(orange));
		show_user_help("you want the portal to point to.",
			buffer, 1, get_color(orange));
		show_user_help("Use Mouse right click to cancel.",
			buffer, 2, get_color(orange));
	}
	if (action->delete)
		show_user_help("Click entity or sector you wish to delete.",
			buffer, 0, get_color(orange));
	if (action->assign_player_start)
		show_user_help("Click sector where you wish player to start.",
			buffer, 0, get_color(orange));
	if (action->assign_end_sector)
		show_user_help("Click sector what you wish to be an end sector.",
			buffer, 0, get_color(orange));
	draw_help_text_two(action, buffer);
}

void	draw_int_string_input(t_buffer *buffer, t_action *action,
		unsigned char **int_string)
{
	if (action->edit_ceiling_height)
		show_user_help(
			"Input new ceiling height using number keys (-99 -- 99):",
			buffer, 0, get_color(orange));
	if (action->edit_floor_height)
		show_user_help("Input new floor height using number keys (-99 -- 99):",
			buffer, 0, get_color(orange));
	if (action->set_light_intensity)
		show_user_help("Set new light intensity using number keys (0-100):",
			buffer, 0, get_color(orange));
	if (action->set_all_sector_ceiling_heights)
		show_user_help("Set new ceiling height for all walls (-99 -- 99):",
			buffer, 0, get_color(orange));
	if (action->set_all_sector_floor_heights)
		show_user_help("Set new floor height for all walls (-99 -- 99):",
			buffer, 0, get_color(orange));
	if (action->edit_floor_height || action->edit_ceiling_height
		|| action->set_light_intensity || action->set_all_sector_ceiling_heights
		|| action->set_all_sector_floor_heights)
	{
		if (*int_string != NULL)
			show_user_help((char *)*int_string, buffer, 1, get_color(white));
	}
}

static void	draw_story_input(unsigned char *string, t_buffer *buffer)
{
	int		i;
	int		lines;
	char	**arr;
	if (!string)
		return ;
	i = 0;
	lines = get_nbr_of_lines(string);
	arr = ft_strsplit((const char *)string, '\n');
	if (arr)
	{
		while (i < lines && arr[i])
		{
			show_user_help(arr[i], buffer, i + 3, get_color(white));
			i++;
		}
		free_array((unsigned char **)arr);
	}
}

void	draw_input_string(unsigned char *string, t_buffer *buffer, int help_text)
{
	if (help_text == map_saving)
	{
		show_user_help(
			"Please input text string:", buffer, 0, get_color(orange));
		if (string != NULL)
			show_user_help((char *)string, buffer, 1, get_color(orange));
	}
	if (help_text == story_string)
	{
		show_user_help("Please input sector story string.",
			buffer, 0, get_color(orange));
		show_user_help("Add newlines with 'Tab' key.",
			buffer, 1, get_color(orange));
		show_user_help("End writing and save plot with 'Return' key.",
			buffer, 2, get_color(orange));
		if (string != NULL)
			draw_story_input(string, buffer);
	}
}

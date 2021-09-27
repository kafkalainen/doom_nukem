/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_texture_strings.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:40:29 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 13:55:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	display_door_tex_string_logic3(t_xy coord, int type,
			t_plx_modifier mod, t_buffer *buffer)
{
	if (type >= DOOR_INDEX)
	{
		mod.len = 11;
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "normal door", mod);
	}
	else
	{
		mod.len = 7;
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "doorway", mod);
	}
}

static void	display_door_tex_string_logic2(t_xy coord, int type,
			t_plx_modifier mod, t_buffer *buffer)
{
	if (type >= MILITARY_INDEX)
	{
		mod.len = 13;
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "military door", mod);
		return ;
	}
	else if (type >= ENGINEERING_INDEX)
	{
		mod.len = 16;
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "engineering door", mod);
		return ;
	}
	else if (type >= CLEANING_INDEX)
	{
		mod.len = 13;
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "cleaning door", mod);
		return ;
	}
	display_door_tex_string_logic3(coord, type, mod, buffer);
}

static void	display_door_tex_string_logic1(t_xy coord, int type,
			t_plx_modifier mod, t_buffer *buffer)
{
	if (type >= LARGE_WINDOW_INDEX)
	{
		mod.len = 12;
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "large window", mod);
		return ;
	}
	else if (type >= SMALL_WINDOW_INDEX)
	{
		mod.len = 12;
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "small window", mod);
		return ;
	}
	else if (type >= SECRET_INDEX)
	{
		mod.len = 11;
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "secret door", mod);
		return ;
	}
	display_door_tex_string_logic2(coord, type, mod, buffer);
}

void	display_door_tex_string(t_editor_walls *wall, t_buffer *buffer)
{
	t_plx_modifier	mod;
	t_xy			coord;

	coord = vec2(10, 218);
	mod.size = TEXT_SIZE;
	mod.colour = get_color(white);
	display_door_tex_string_logic1(coord, wall->type, mod, buffer);
}

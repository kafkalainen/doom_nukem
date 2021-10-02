/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_textfields.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:08:33 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/02 16:32:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	display_wall_tex(t_editor_walls *wall, t_buffer *buffer,
	t_texture **textures, t_box *box)
{
	t_texel			*tex;

	tex = get_tex(wall->type, textures);
	draw_image_static(box->start, tex, buffer,
		(float)(ft_fabsf(box->end.x - box->start.x) / tex->width));
}

static t_texel	*get_door_tex(t_editor_walls *wall, t_texture **textures)
{
	t_texel			*tex;

	tex = get_tex(-door, textures);
	if (wall->type >= LARGE_WINDOW_INDEX)
		tex = get_tex(-large_window, textures);
	else if (wall->type >= SMALL_WINDOW_INDEX
		&& wall->type < LARGE_WINDOW_INDEX)
		tex = get_tex(-small_window, textures);
	else if (wall->type >= MILITARY_INDEX && wall->type < SECRET_INDEX)
		tex = get_tex(-military_keycard_sprite, textures);
	else if (wall->type >= ENGINEERING_INDEX && wall->type < MILITARY_INDEX)
		tex = get_tex(-engineering_keycard_sprite, textures);
	else if (wall->type >= CLEANING_INDEX && wall->type < ENGINEERING_INDEX)
		tex = get_tex(-cleaning_keycard_sprite, textures);
	return (tex);
}

static void	display_door_tex(t_editor_walls *wall, t_buffer *buffer,
	t_texture **textures, t_box *box)
{
	t_editor_walls	*prev;
	t_texel			*tex;

	if (wall->type >= SECRET_INDEX
		&& wall->type < (SECRET_INDEX + DOOR_INDEX))
	{
		prev = wall;
		while (prev->next->idx != wall->idx)
			prev = prev->next;
		if (prev->type < 0)
			tex = get_tex(prev->type, textures);
		else
			tex = get_tex(-2, textures);
		draw_image_static(box->start, tex, buffer,
			(float)(ft_fabsf(box->end.x - box->start.x) / tex->width));
	}
	else if (wall->type < LARGE_WINDOW_INDEX)
	{
		tex = get_door_tex(wall, textures);
		draw_image_static(box->start, tex, buffer,
			(float)(ft_fabsf(box->end.x - box->start.x) / tex->width));
	}
}

static void	draw_wall_info(t_editor_walls *wall, t_buffer *buffer)
{
	t_plx_modifier	mod;
	char			*temp;

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	temp = ft_itoa(wall->idx);
	mod.len = ft_strlen(temp);
	ft_str_pxl(buffer, vec2(260, 56), temp, mod);
	ft_strdel(&temp);
	temp = ft_itoa(wall->height.ceiling);
	mod.len = ft_strlen(temp);
	ft_str_pxl(buffer, vec2(260, 251), temp, mod);
	ft_strdel(&temp);
	temp = ft_itoa(wall->height.ground);
	mod.len = ft_strlen(temp);
	ft_str_pxl(buffer, vec2(260, 281), temp, mod);
	ft_strdel(&temp);
}

void	draw_wall_textfields(t_editor_walls *wall,
	t_buffer *buffer, t_texture **textures)
{
	t_box			box;

	if (!wall)
		return ;
	box.start = vec2(100, 110);
	box.end = vec2(200, 210);
	draw_wall_info(wall, buffer);
	if (wall->type < 0)
		display_wall_tex(wall, buffer, textures, &box);
	else if (wall->type < DOOR_INDEX)
	{
		display_door_tex_string(wall, buffer);
	}
	else
	{
		display_door_tex(wall, buffer, textures, &box);
		display_door_tex_string(wall, buffer);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_textfields.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:08:33 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/17 16:24:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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
	ft_str_pxl(buffer, vec2(260, 221), temp, mod);
	ft_strdel(&temp);
	temp = ft_itoa(wall->height.ground);
	mod.len = ft_strlen(temp);
	ft_str_pxl(buffer, vec2(260, 251), temp, mod);
	ft_strdel(&temp);
}

void	draw_wall_textfields(t_editor_walls *wall,
	t_buffer *buffer, t_texture **textures)
{
	t_box			box;
	t_texel			*tex;

	if (!wall)
		return ;
	box.start = vec2(100, 110);
	box.end = vec2(200, 220);
	draw_wall_info(wall, buffer);
	if (wall->type < 0)
	{
		tex = get_tex(wall->type, textures);
		draw_image_static(box.start, tex, buffer,
			(float)(ft_fabsf(box.end.x - box.start.x) / tex->width));
	}
	else if (wall->type < 3000)
		return ;
	else
	{
		tex = get_tex(-door, textures);
		draw_image_static(box.start, tex, buffer,
			(float)(ft_fabsf(box.end.x - box.start.x) / tex->width));
	}
}

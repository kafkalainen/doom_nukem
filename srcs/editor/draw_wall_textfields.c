/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_textfields.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:08:33 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/15 18:08:53 by rzukale          ###   ########.fr       */
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
	ft_str_pxl(buffer, vec2(165, 56), temp, mod);
	ft_strdel(&temp);
	temp = ft_itoa(wall->height.ceiling);
	mod.len = ft_strlen(temp);
	ft_str_pxl(buffer, vec2(255, 258), temp, mod);
	ft_strdel(&temp);
	temp = ft_itoa(wall->height.ground);
	mod.len = ft_strlen(temp);
	ft_str_pxl(buffer, vec2(255, 288), temp, mod);
	ft_strdel(&temp);
}

void	draw_wall_textfields(t_editor_walls *wall,
	t_buffer *buffer, t_texture **textures)
{
	t_box			box;
	float			scale;
	t_texel			*tex;

	if (!wall)
		return ;
	draw_wall_info(wall, buffer);
	if (wall->type < 0)
	{
		box.start = vec2(32, 110);
		box.end = vec2(132, 220);
		tex = get_tex(wall->type, textures);
		scale = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
		draw_image(box.start, tex, buffer, scale);
	}
}

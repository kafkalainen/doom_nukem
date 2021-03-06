/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sector_textfields.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:06:36 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/01 14:47:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_sector_textfield_textures(t_editor_sector *sector,
	t_buffer *buffer, t_texture **textures)
{
	t_box			box;
	float			scale;
	t_texel			*tex;

	box.start = vec2(100, 110);
	box.end = vec2(200, 210);
	tex = get_tex(sector->tex_floor, textures);
	scale = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
	draw_image_static(box.start, tex, buffer, scale);
	box.start = vec2(100, 245);
	box.end = vec2(200, 345);
	tex = get_tex(sector->tex_ceil, textures);
	scale = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
	draw_image_static(box.start, tex, buffer, scale);
}

static void	draw_gravity_choice(t_editor_sector *sector, t_buffer *buffer,
	t_plx_modifier mod)
{
	t_xy	coord;

	coord.y = 591;
	mod.len = 7;
	if (sector->gravity == 2)
	{
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "lunar", mod);
	}
	if (sector->gravity == 4)
	{
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "martian", mod);
	}
	if (sector->gravity == 10)
	{
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "earth", mod);
	}
	if (sector->gravity == 23)
	{
		coord.x = center_text_x_axis(0, 295, mod.size, mod.len);
		ft_str_pxl(buffer, coord, "jupiter", mod);
	}
}

void	draw_sector_textfields(t_editor_sector *sector,
	t_buffer *buffer, t_texture **textures)
{
	t_plx_modifier	mod;
	char			*temp;

	if (!sector)
		return ;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	temp = ft_itoa(sector->idx_sector);
	mod.len = ft_strlen(temp) + 1;
	ft_str_pxl(buffer, vec2(250, 56), temp, mod);
	ft_strdel(&temp);
	temp = ft_itoa(sector->light.intensity);
	mod.len = ft_strlen(temp) + 1;
	ft_str_pxl(buffer, vec2(250, 416), temp, mod);
	ft_strdel(&temp);
	draw_sector_textfield_textures(sector, buffer, textures);
	draw_gravity_choice(sector, buffer, mod);
}

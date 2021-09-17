/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity_textfields.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:07:32 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/17 17:02:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	reset_multisprite_values(t_screen_xy *current, t_uvz *txl, int i)
{
	if (i == 0)
	{
		*current = (t_screen_xy){0, 0};
		*txl = (t_uvz){0.0f, 0.0f, 1.0f};
	}
	else
	{
		current->x = 0;
		txl->u = 0.0f;
	}
}

void	draw_multisprite_image(t_xy offset, t_texel *tex,
	t_buffer *buffer, t_xy scale)
{
	t_screen_xy	current;
	t_screen_xy	image;
	t_uvz		txl;
	t_uv		cur_texel;

	reset_multisprite_values(&current, &txl, 0);
	image = (t_screen_xy){TEX_SIZE * scale.w, TEX_SIZE * scale.w};
	scale.x = 0.1f / (TEX_SIZE * scale.w);
	scale.y = 0.166666667f / (TEX_SIZE * scale.w);
	while (current.y < image.y)
	{
		reset_multisprite_values(&current, &txl, 1);
		while (current.x < image.x)
		{
			cur_texel.v = txl.v * (tex->height - 1);
			cur_texel.u = txl.u * (tex->width - 1);
			put_pixel(buffer, (t_pxl_coords){current.x + offset.x,
				current.y + offset.y},
				(Uint32)tex->texels[cur_texel.v * tex->width + cur_texel.u]);
			current.x++;
			txl.u += scale.x;
		}
		txl.v += scale.y;
		current.y++;
	}
}

static void	draw_entity_textures(t_entity_list *entity,
	t_buffer *buffer, t_texture **textures)
{
	t_texel			*tex;
	t_xy			scale;
	t_box			box;

	box.start = vec2(100, 110);
	box.end = vec2(200, 220);
	draw_box(box, buffer, get_color(black));
	tex = get_tex(editor_select_entity_tex(entity->entity_type), textures);
	if (entity->entity_type == skull_skulker || entity->entity_type == thing
		|| entity->entity_type == drone || entity->entity_type == crewmember)
	{
		scale.w = (float)(ft_fabsf(box.end.x - box.start.x) / 128);
		scale.x = 128;
		scale.y = 128;
		draw_multisprite_image(box.start, tex, buffer, scale);
	}
	else
	{
		scale.w = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
		draw_image_static(box.start, tex, buffer, scale.w);
	}
}

void	draw_entity_textfields(t_entity_list *entity,
	t_buffer *buffer, t_texture **textures)
{
	t_plx_modifier	mod;
	char			*str;

	if (!entity)
		return ;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	str = ft_itoa(entity->entity_idx);
	mod.len = ft_strlen(str) + 1;
	ft_str_pxl(buffer, vec2(265, 56), str, mod);
	ft_strdel(&str);
	str = ft_itoa(entity->entity_type);
	mod.len = ft_strlen(str) + 1;
	ft_str_pxl(buffer, vec2(265, 84), str, mod);
	ft_strdel(&str);
	mod.len = 1;
	ft_c_pxl(buffer, vec2(265, 231), '0' + entity->is_linked, mod);
	ft_c_pxl(buffer, vec2(265, 261), '0' + entity->is_revealed, mod);
	ft_c_pxl(buffer, vec2(265, 291), '0' + entity->state, mod);
	draw_entity_textures(entity, buffer, textures);
}

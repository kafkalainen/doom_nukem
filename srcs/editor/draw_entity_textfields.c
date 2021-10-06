/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity_textfields.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:07:32 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/06 09:49:50 by jnivala          ###   ########.fr       */
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
	image = (t_screen_xy){scale.x * scale.w, scale.y * scale.w};
	scale.x = 0.1f / (scale.x * scale.w);
	scale.y = 0.166666667f / (scale.y * scale.w);
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

	box = (t_box){vec2(100, 110), vec2(200, 220)};
	draw_box(box, buffer, get_color(black));
	tex = get_tex(editor_select_entity_tex(entity->type, entity->is_revealed),
		textures);
	if (is_enemy(entity->type))
	{
		if (entity->type == skull_skulker || entity->type == drone)
			scale = (t_xy){SMALL_ENEMY, SMALL_ENEMY,
				(float)(ft_fabsf(box.end.x - box.start.x) / SMALL_ENEMY)};
		else if (entity->type == thing || entity->type == crewmember)
			scale = (t_xy){LARGE_ENEMY, LARGE_ENEMY,
				(float)(ft_fabsf(box.end.x - box.start.x) / LARGE_ENEMY)};
		draw_multisprite_image(box.start, tex, buffer, scale);
	}
	else
	{
		if (entity->type == powerstation)
			scale.w = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
		else
			scale.w = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
		draw_image_static(box.start, tex, buffer, scale.w);
	}
}

static void	draw_light_modes(t_buffer *buffer, t_entity_list *entity,
			t_plx_modifier *mod)
{
	if (entity->is_linked == 0)
	{
		mod->len = 4;
		ft_str_pxl(buffer, vec2(245, 231), "none", *mod);
	}
	else if (entity->is_linked == 1)
	{
		mod->len = 4;
		ft_str_pxl(buffer, vec2(245, 231), "auto", *mod);
	}
	else
		ft_c_pxl(buffer, vec2(265, 231), '0' + entity->is_linked, *mod);
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
	str = ft_itoa(entity->type);
	mod.len = ft_strlen(str) + 1;
	ft_str_pxl(buffer, vec2(265, 84), str, mod);
	ft_strdel(&str);
	mod.len = 1;
	draw_light_modes(buffer, entity, &mod);
	ft_c_pxl(buffer, vec2(265, 261), '0' + entity->is_revealed, mod);
	ft_c_pxl(buffer, vec2(265, 291), '0' + entity->state, mod);
	draw_entity_textures(entity, buffer, textures);
}

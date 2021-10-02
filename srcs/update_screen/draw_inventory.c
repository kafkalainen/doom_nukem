/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:38:15 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/02 09:42:30 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_inventory_slots(t_player *plr, t_buffer *buffer)
{
	int			i;
	int			gap;
	t_xy		size;
	t_screen_xy	offset;
	t_uint		colour;

	i = -2;
	gap = 12;
	offset = (t_screen_xy){SCREEN_WIDTH * 0.5f, 562};
	size = vec2(32, 32);
	while (i < 2)
	{
		if (plr->active_inv == i + 2)
			colour = colour_scale(0xFFDDDD00, 1.0f, buffer->lightness, 1.0f);
		else
			colour = colour_scale(0xFF202020, 1.0f, buffer->lightness, 1.0f);
		draw_rect(vec2(offset.x + i * (size.x + gap) - gap * 0.25,
				offset.y - gap * 0.25), vec2(size.x + gap * 0.5,
				size.y + gap * 0.5), buffer, colour);
		draw_rect(vec2(offset.x + i * (size.x + gap),
				offset.y), vec2(size.x, size.y), buffer,
			colour_scale(0xFF734D54, 1.0f, buffer->lightness, 1.0f));
		i++;
	}
}

void	draw_image(t_xy offset, t_texel *tex, t_buffer *buffer, float scale)
{
	t_screen_xy	current;
	t_screen_xy	image;
	Uint32		texel;

	current.x = 0;
	current.y = 0;
	image.x = tex->height * scale;
	image.y = tex->width * scale;
	scale = 1 / scale;
	while (current.y < image.y)
	{
		current.x = 0;
		while (current.x < image.x)
		{
			texel = (Uint32)tex->texels[(tex->width * current.y
					* (int)scale) + current.x * (int)scale];
			put_pixel(
				buffer,
				(t_pxl_coords){current.x + offset.x,
				current.y + offset.y},
				colour_scale(texel, 1.0f, buffer->lightness, 1.0f));
			current.x++;
		}
		current.y++;
	}
}

void	draw_inventory_images(t_home *home, t_player *plr, t_buffer *buffer)
{
	int			i;
	int			gap;
	t_screen_xy	offset;
	t_texel		tex;

	i = -2;
	gap = 12;
	offset.x = SCREEN_WIDTH * 0.5f;
	offset.y = 562;
	while (i < 2)
	{
		if (plr->inventory[i + 2].in_use)
		{
			tex = home->textures[plr->inventory[i + 2].sprite_idx]->tex;
			draw_image(vec2(offset.x + i * (32 + gap),
					offset.y), &tex, buffer, 0.25f);
		}
		i++;
	}
}

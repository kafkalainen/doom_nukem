/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:38:15 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 15:27:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static Uint32	light_colour(Uint32 colour, float *lightness)
{
	if (*lightness < 1.0f)
		colour = colour_scale(colour, 1.0f, *lightness, 1.0f);
	return (colour);
}

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
			colour = light_colour(0xFFDDDD00, &buffer->lightness);
		else
			colour = light_colour(0xFF202020, &buffer->lightness);
		draw_rect(vec2(offset.x + i * (size.x + gap) - gap * 0.25,
				offset.y - gap * 0.25), vec2(size.x + gap * 0.5,
				size.y + gap * 0.5), buffer, colour);
		draw_rect(vec2(offset.x + i * (size.x + gap),
				offset.y), vec2(size.x, size.y), buffer,
			light_colour(0xFF734D54, &buffer->lightness));
		i++;
	}
}

void	draw_image(t_xy offset, t_texel *tex, t_buffer *buffer, float scale)
{
	t_screen_xy	current;
	t_screen_xy	image;
	Uint32		texel;

	current = (t_screen_xy){0, 0};
	image = (t_screen_xy){tex->width * scale, tex->height * scale};
	scale = 1 / scale;
	while (current.y < image.y)
	{
		current.x = 0;
		while (current.x < image.x)
		{
			texel = (Uint32)tex->texels[(tex->width * current.y
					* (int)scale) + current.x * (int)scale];
			if (buffer->lightness < 1.0f)
				texel = colour_scale(texel, 1.0f, buffer->lightness, 1.0f);
			put_pixel(
				buffer, (t_pxl_coords){current.x + offset.x,
				current.y + offset.y}, texel);
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

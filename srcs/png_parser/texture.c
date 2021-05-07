/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:16:50 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/07 12:37:12 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	swap_channels(unsigned int color)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	alpha;

	red = (color & 0xFF000000) >> 24;
	green = (color & 0x00FF0000) >> 16;
	blue = (color & 0x0000FF00) >> 8;
	alpha = (color & 0x000000FF);
	return ((alpha << 24) | (red << 16) | (green << 8) | (blue));
}

unsigned int	add_pixel(unsigned char *data, int bpp, int pos)
{
	int				i;
	int				shift;
	unsigned int	pixel;

	i = 0;
	shift = bpp - 1;
	pixel = 0;
	while (i < bpp)
	{
		pixel |= (data[pos++] << (8 * shift--));
		i++;
	}
	return (pixel);
}

void	convert_to_unsigned_int(t_texture *tex, t_png *png)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < png->height)
	{
		x = 0;
		while (x < png->width)
		{
			tex->pixels[(y * tex->w) + x] = add_pixel(png->pixels, tex->bpp,
					((y * tex->pitch) + x * tex->bpp));
			x++;
		}
		y++;
	}
}

t_texture	*create_texture(t_png *png, int idx)
{
	t_texture	*tex;

	tex = (t_texture *)malloc(sizeof(t_texture));
	if (!tex)
		error_output("Memory allocation of t_texture struct failed\n");
	tex->source = (unsigned char *)malloc(sizeof(unsigned char)
			* png->source.size);
	if (!tex->source)
		error_output("Memory allocation of editor pixel pointer failed\n");
	ft_memcpy(tex->source, png->source.buf, png->source.size);
	tex->h = png->height;
	tex->w = png->width;
	tex->bpp = (png->depth / 8) * png->channels;
	tex->size = png->final_size;
	tex->color_depth = png->depth;
	tex->color_type = png->color_type;
	tex->format = png->format;
	tex->source_size = png->source.size;
	tex->pitch = (tex->w * tex->bpp);
	tex->idx = idx;
	tex->pixels = (unsigned int *)malloc(sizeof(unsigned int)
			* (tex->h * tex->pitch));
	if (!tex->pixels)
		error_output("Memory allocation of pixel pointer failed\n");
	convert_to_unsigned_int(tex, png);
	return (tex);
}

void	free_texture(t_texture *tex)
{
	free(tex->source);
	free(tex->pixels);
	free(tex);
}

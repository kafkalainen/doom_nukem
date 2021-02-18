/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:16:50 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/18 16:15:04 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/png_parser.h"

unsigned int	swap_channels(unsigned int color)
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;

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

void			convert_to_unsigned_int(t_texture *tex, t_png *png)
{
	unsigned int x;
	unsigned int y;

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

t_texture		*create_texture(t_png *png)
{
	t_texture	*tex;

	if (!(tex = (t_texture*)malloc(sizeof(t_texture))))
		error_output("malloc error\n");
	tex->h = png->height;
	tex->w = png->width;
	tex->bpp = (png->depth / 8) * png->channels;
	tex->size = png->final_size;
	tex->color_depth = png->depth;
	tex->color_type = png->color_type;
	tex->format = png->format;
	tex->pitch = (tex->w * tex->bpp);
	if (!(tex->pixels = (unsigned int *)malloc(sizeof(unsigned int) *
		(tex->h * tex->pitch))))
		error_output("malloc error\n");
	convert_to_unsigned_int(tex, png);
	return (tex);
}

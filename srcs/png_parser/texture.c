/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:16:50 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/11 12:51:06 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	swap_channels(unsigned int color, int format)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	alpha;

	if (format == RGB_8 || format == RGB_16)
	{
		alpha = 0xFF;
		red = (color & 0xFF0000) >> 16;
		green = (color & 0x00FF00) >> 8;
		blue = (color & 0x0000FF);
	}
	else
	{
		red = (color & 0xFF000000) >> 24;
		green = (color & 0x00FF0000) >> 16;
		blue = (color & 0x0000FF00) >> 8;
		alpha = (color & 0x000000FF);
	}
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
			tex->tex.texels[(y * tex->tex.width) + x] = add_pixel(png->pixels, tex->bpp,
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
	add_texture_values(png, tex, idx);
	tex->tex.texels = (unsigned int *)malloc(sizeof(unsigned int)
			* (tex->tex.height * tex->pitch));
	if (!tex->tex.texels)
		error_output("Memory allocation of pixel pointer failed\n");
	convert_to_unsigned_int(tex, png);
	return (tex);
}

void	free_texture(t_texture *tex)
{
	if (tex->source != NULL)
	{
		free(tex->source);
		tex->source = NULL;
	}
	if (tex->tex.texels != NULL)
	{
		free(tex->tex.texels);
		tex->tex.texels = NULL;
	}
	if (tex != NULL)
	{
		free(tex);
		tex = NULL;
	}
}

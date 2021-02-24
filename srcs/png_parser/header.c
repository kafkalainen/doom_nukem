/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:51:32 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/24 12:13:53 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	validate_signature(unsigned char *buf)
{
	int						i;
	static unsigned char	sig[8] = {137, 80, 78,
							71, 13, 10, 26, 10};

	i = -1;
	while (++i < 8)
	{
		if (buf[i] != sig[i])
			error_output("Signature does not match\n");
	}
}

int		get_format(int color_type, int color_depth)
{
	if (color_type == COLOR_LUM)
	{
		return (get_color_lum(color_depth));
	}
	else if (color_type == COLOR_RGB)
	{
		return (get_color_rgb(color_depth));
	}
	else if (color_type == COLOR_LUMA)
	{
		return (get_color_luma(color_depth));
	}
	else if (color_type == COLOR_RGBA)
	{
		return (get_color_rgba(color_depth));
	}
	else
		return (-1);
}

void	get_header_elements(t_png *png)
{
	png->width = get_big_endian(png->source.buf + 16);
	png->height = get_big_endian(png->source.buf + 20);
	png->depth = png->source.buf[24];
	png->color_type = png->source.buf[25];
	png->format = get_format(png->color_type, png->depth);
	if (!png->format)
		error_output("Bad color format\n");
	png->compression_method = png->source.buf[26];
	png->filter_method = png->source.buf[27];
	png->interlace_method = png->source.buf[28];
	if (png->color_type == 2 || png->color_type == 6)
		png->channels = (png->color_type == 2) ? 3 : 4;
	else if (!png->color_type || png->color_type == 4)
		png->channels = (!png->color_type) ? 1 : 2;
	if (png->channels)
	{
		png->bpp = png->depth * png->channels;
		png->scanline = png->bpp * png->width + 1;
	}
}

int		color_depth_restrictions(int color, int depth)
{
	if (color == 0 && (depth == 1 || depth == 2 ||
		depth == 4 || depth == 8 || depth == 16))
		return (1);
	else if (color == 2 && (depth == 8 || depth == 16))
		return (1);
	else if (color == 3 && (depth == 1 || depth == 2 ||
		depth == 4 || depth == 8))
		return (1);
	else if (color == 4 && (depth == 8 || depth == 16))
		return (1);
	else if (color == 6 && (depth == 8 || depth == 16))
		return (1);
	return (0);
}

void	check_header(t_png *png)
{
	if (png->chunk.size != 13 || png->state != 0 || png->source.size < 29)
		error_output("Error reading file header\n");
	get_header_elements(png);
	if (png->width == 0 || png->height == 0 || !png->width || !png->height)
		error_output("Image dimension error\n");
	if (png->depth > 16 || !check_depth(png->depth))
		error_output("Depth error\n");
	if (!color_depth_restrictions(png->color_type, png->depth))
		error_output("Color type - depth is mismatched\n");
	if (png->color_type > 6 || png->color_type == 1 || png->color_type == 5)
		error_output("Color type not allowed\n");
	png->state = 1;
}

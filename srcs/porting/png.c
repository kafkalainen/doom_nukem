/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/14 18:01:38 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	*convert_to_uint32(Uint32 *dest, t_texture *image)
{
	int		x;
	int		y;
	Uint32	*pixels;

	pixels = (Uint32 *)image->tex.texels;
	y = -1;
	while (++y < image->tex.height)
	{
		x = -1;
		while (++x < image->tex.width)
		{
			dest[(y * image->tex.width) + x] = swap_channels(pixels[(y
						* image->tex.width) + x], image->format);
		}
	}
	return (dest);
}

void	load_texture(char *path, t_texture **tex_array, int i)
{
	t_png	png;

	ft_putstr("Loading texture: ");
	ft_putstr(path);
	ft_putchar('\n');
	png = png_parser(path);
	tex_array[i] = create_texture(&png, (i * (-1)));
	if (!tex_array[i])
		error_output("PNG image file loading failed\n");
	else
		convert_to_uint32(tex_array[i]->tex.texels, tex_array[i]);
	free_png(png);
}

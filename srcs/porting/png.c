/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/03 16:12:41 by jnivala          ###   ########.fr       */
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

	printf("%s\n", path);
	png = png_parser(path);
	tex_array[i] = create_texture(&png, (i * (-1)));
	if (!tex_array[i])
		error_output("PNG image file loading failed\n");
	else
		convert_to_uint32(tex_array[i]->tex.texels, tex_array[i]);
	free_png(png);
}

/*
** Init textures for editor
*/

void	cycle_textures(t_home *home, struct dirent *dir_entry, DIR *dir)
{
	int		i;
	char	*found;
	char	*buf;

	i = 2;
	dir_entry = readdir(dir);
	while (dir_entry != NULL)
	{
		found = ft_strstr(dir_entry->d_name, ".png");
		if (found != NULL && ft_strcmp(dir_entry->d_name, "dsky.png") != 0)
		{
			printf("%s index: %i\n", dir_entry->d_name, i);
			buf = ft_strjoin("textures/", dir_entry->d_name);
			load_texture(buf, home->textures, i++);
			ft_strdel(&buf);
		}
		dir_entry = readdir(dir);
	}
}

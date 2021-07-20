/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/07/06 16:59:29 by jnivala          ###   ########.fr       */
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
	// load_texture("textures/face.png", home->textures, i);
	load_texture("sprites/hud_doom.png", home->textures, i);
	// load_texture("sprites/skull_skulker_front.png", home->textures, i); // might need to do some magic with index nbr
	// load_texture("sprites/skull_skulker_attack_1.png", home->textures, i);
	// printf("%i\n", i);
}


void	init_textures(t_home *home)
{
	home->textures = (t_texture **)malloc(sizeof(t_texture *)
			* NUM_TEX + 1);
	if (!home->textures)
		error_output("Failed to allocate memory to editor textures.\n");
	home->textures[zero] = assign_empty_texture();
	load_texture("textures/dsky.png", home->textures, space);
	load_texture("textures/armory.png", home->textures, wall0);
	load_texture("textures/checkers.png", home->textures, wall1);
	load_texture("textures/checkers2.png", home->textures, wall2);
	load_texture("textures/face.png", home->textures, wall3);
	load_texture("textures/hull.png", home->textures, wall4);
	load_texture("textures/hull2.png", home->textures, wall5);
	load_texture("textures/loading_bay.png", home->textures, wall6);
	load_texture("textures/door.png", home->textures, door);
	load_texture("textures/enemy0.png", home->textures, enemy0);
}
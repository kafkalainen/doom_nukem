/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/15 14:37:49 by rzukale          ###   ########.fr       */
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

void	load_texture(char *path, t_home *home, int i)
{
	t_png	png;

	png = png_parser(path);
	home->textures[i] = create_texture(&png, (i * (-1)));
	if (!home->textures[i])
		error_output("PNG image file loading failed\n");
	else
		convert_to_uint32(home->textures[i]->tex.texels, home->textures[i]);
	// printf("format: %i\n", png.format);
	free_png(png);
}

static void	get_tex_count(int *i, DIR **dir, struct dirent **dir_entry)
{
	char	*found;

	(*i) = 0;
	*dir_entry = readdir(*dir);
	while (*dir_entry != NULL)
	{
		found = ft_strstr((*dir_entry)->d_name, ".png");
		if (found != NULL)
			(*i)++;
		*dir_entry = readdir(*dir);
	}
	rewinddir(*dir);
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
			load_texture(buf, home, i++);
			ft_strdel(&buf);
		}
		dir_entry = readdir(dir);
	}
}

void	init_textures(t_home *home)
{
	DIR				*dir;
	struct dirent	*dir_entry;

	dir = opendir("textures/");
	if (dir == NULL)
		error_output("Failed to open textures directory.\n");
	get_tex_count(&home->nbr_of_textures, &dir, &dir_entry);
	if (home->nbr_of_textures == 0)
		error_output("No textures found\n");
	home->textures = (t_texture **)malloc(sizeof(t_texture *)
			* (home->nbr_of_textures + 1));
	if (!home->textures)
		error_output("Failed to allocate memory to editor textures.\n");
	home->textures[0] = assign_empty_texture();
	load_texture("textures/dsky.png", home, 1);
	cycle_textures(home, dir_entry, dir);
	closedir(dir);
}

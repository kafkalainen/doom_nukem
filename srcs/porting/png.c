/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/17 13:10:29 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	*convert_to_uint32(Uint32 *dest, t_texture *image)
{
	int		x;
	int		y;
	Uint32	*pixels;

	pixels = (Uint32 *)image->pixels;
	y = -1;
	while (++y < image->h)
	{
		x = -1;
		while (++x < image->w)
		{
			dest[(y * image->w) + x] = swap_channels(pixels[(y
						* image->w) + x]);
		}
	}
	return (dest);
}

void	load_texture(char *path, t_home *home, int i)
{
	t_png	png;

	png = png_parser(path);
	home->editor_tex[i] = create_texture(&png, (i * (-1)));
	if (home->editor_tex[i] == NULL)
		error_output("PNG image file loading failed\n");
	else
		convert_to_uint32(home->editor_tex[i]->pixels, home->editor_tex[i]);
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

	i = 1;
	dir_entry = readdir(dir);
	while (dir_entry != NULL)
	{
		found = ft_strstr(dir_entry->d_name, ".png");
		if (found != NULL)
		{
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
	home->editor_tex = (t_texture **)malloc(sizeof(t_texture *)
			* (home->nbr_of_textures + 1));
	if (!home->editor_tex)
		error_output("Failed to allocate memory to editor textures.\n");
	home->editor_tex[0] = assign_empty_texture();
	cycle_textures(home, dir_entry, dir);
	closedir(dir);
}

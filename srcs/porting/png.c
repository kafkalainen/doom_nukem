/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/21 17:44:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	*convert_to_uint32(Uint32 *dest, t_texture *image)
{
	int		x;
	int		y;
	Uint32	*pixels;

	pixels = (Uint32*)image->pixels;
	y = -1;
	while (++y < image->h)
	{
		x = -1;
		while (++x < image->w)
		{
			dest[(y * image->w) + x] = swap_channels(pixels[(y * image->w) + x]);
		}
	}
	return (dest);
}

Uint32		get_texel(int x, int y, t_texture *tex)
{
	int offset_x;
	int offset_y;

	offset_x = x % tex->w;
	offset_y = y % tex->h;
	return ((Uint32)tex->pixels[(offset_y * tex->w) + offset_x]);
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

static void		get_tex_count(int *i, DIR **dir, struct dirent **dir_entry)
{
	char	*found;

	(*i) = 0;
	while ((*dir_entry = readdir(*dir)) != NULL)
	{
		found = ft_strstr((*dir_entry)->d_name, ".png");
		if (found != NULL)
			(*i)++;
	}
	rewinddir(*dir);
}

/*
** Init textures for editor
*/

void	init_textures(t_home *home)
{
	DIR				*dir;
	struct dirent	*dir_entry;
	int				i;
	char			*found;
	char			*buf;

	if ((dir = opendir("textures/")) == NULL)
		error_output("Failed to open textures directory\n");
	get_tex_count(&home->nbr_of_textures, &dir, &dir_entry);
	if (!(home->editor_tex = (t_texture**)malloc(sizeof(t_texture*) * (home->nbr_of_textures + 1))))
		error_output("failed to allocate memory to editor textures\n");
	home->editor_tex[0] = NULL;
	i = 1;
	while ((dir_entry = readdir(dir)) != NULL)
	{
		if ((found = ft_strstr(dir_entry->d_name, ".png")) != NULL)
		{
			buf = ft_strjoin("textures/", dir_entry->d_name);
			load_texture(buf, home, i++);
			ft_strdel(&buf);
		}
	}
	closedir(dir);
}

/*
** 1st pass at loading char* and converting back to t_texture. Need to see text output before making further changes
*/

void		free_array(unsigned char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_strdel((char**)&array[i]);
		i++;
	}
	free(array);
}

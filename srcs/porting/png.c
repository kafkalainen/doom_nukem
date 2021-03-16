/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/12 16:13:00 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

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
	home->editor_tex[i] = png_parser(path);
	if (home->editor_tex[i] == NULL)
		error_output("PNG image file loading failed\n");
	else
		convert_to_uint32(home->editor_tex[i]->pixels, home->editor_tex[i]);
	home->editor_tex[i]->idx = i * (-1);
}

/*
** Change this function to open textures directory, find all ".png" files and load them into the system
** and return the number of textures loaded at home.nbr_of_textures
*/

static void		get_tex_count(int *i, DIR *dir, struct dirent *dir_entry)
{
	char	*found;

	(*i) = 0;
	while ((dir_entry = readdir(dir)) != NULL)
	{
		if ((found = ft_strstr(dir_entry->d_name, ".png")) != NULL)
			(*i)++;
	}
	rewinddir(dir);
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
	get_tex_count(&home->nbr_of_textures, dir, dir_entry);
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

/*
	** Each map data element type is separated by a element tag (eg. #TEX for textures)
	** element tag line for all elements will include element tag, total number of element components (eg. #TEX 9)
	** each element component line will include everything that specific component will need to fully initialize,
	** they will be separated with a break character
	** texture element example:
	** [idx][width] [height] [size] [color_type] [color_depth] [format] [bits_per_pixel] [pitch] [compressed_size] [unsigned char *pixel data]
	** tex idx is determined by the order by which elements are saved into the map data file
	*/


// REDO everything
// t_texture	*load_texture_from_map_data(char *line)
// {
// 	t_texture		*tex;
// 	unsigned char	**elems;

// 	if (!(tex = (t_texture*)malloc(sizeof(t_texture))))
// 		error_output("Memory allocation of t_texture struct failed\n");
// 	elems = (unsigned char**)ft_strsplit(line, '#'); // break character should be a unique character that will not appear in any of the actual data
// 	tex->w = ft_atoi((const char*)elems[0]);
// 	tex->h = ft_atoi((const char*)elems[1]);
// 	tex->size = ft_atoi((const char*)elems[2]);
// 	tex->color_type = ft_atoi((const char*)elems[3]);
// 	tex->color_depth = ft_atoi((const char*)elems[4]);
// 	tex->format = ft_atoi((const char*)elems[5]);
// 	tex->bpp = ft_atoi((const char*)elems[6]);
// 	tex->pitch = ft_atoi((const char*)elems[7]);
// 	if (!(tex->map_pixels = (unsigned char *)malloc(sizeof(unsigned char) * tex->size)))
// 		error_output("Memory allocation of editor pixel pointer failed\n");
// 	ft_memcpy(tex->map_pixels, elems[8], tex->size);
// 	if (!(tex->pixels = (unsigned int *)malloc(sizeof(unsigned int) *
// 		(tex->h * tex->pitch))))
// 		error_output("Memory allocation of pixel pointer failed\n");
// 	convert_editor_tex(tex);
// 	free(tex->map_pixels);
// 	tex->map_pixels = NULL;
// 	free_array(elems);
// 	return (tex);
// }

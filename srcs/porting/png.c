/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/26 11:07:06 by rzukale          ###   ########.fr       */
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
	home->editor_textures[i] = png_parser(path);
	if (home->editor_textures[i] == NULL)
		error_output("PNG image file loading failed\n");
	else
		convert_to_uint32(home->editor_textures[i]->pixels, home->editor_textures[i]);
}

void	init_textures(t_home *home)
{
	if (!(home->editor_textures = (t_texture**)malloc(sizeof(t_texture*) * 6)))
		error_output("failed to allocate memory to editor textures\n");
	home->editor_textures[0] = NULL;
	load_texture("textures/greybrick.png", home, 1);
	load_texture("textures/redbrick.png", home, 2);
	load_texture("textures/wood.png", home, 3);
	load_texture("textures/eagle.png", home, 4);
	load_texture("textures/emal_floor_texture.png", home, 5);
}

/*
** 1st pass at loading char* and converting back to t_texture. Need to see text output before making further changes
*/

void		convert_editor_tex(t_texture *tex)
{
	unsigned int x;
	unsigned int y;

	y = -1;
	while (++y < tex->h)
	{
		x = -1;
		while (++x < tex->w)
		{
			tex->pixels[(y * tex->w) + x] = add_pixel(tex->map_pixels, tex->bpp,
				((y * tex->pitch) + x * tex->bpp));
		}
	}
	convert_to_uint32(tex->pixels, tex);
}

void		free_array(unsigned char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_strdel(&array[i]);
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
	** [width] [height] [size] [color_type] [color_depth] [format] [bits_per_pixel] [pitch] [unsigned char *pixel data]
	** tex idx is determined by the order by which elements are saved into the map data file
	*/

t_texture	*load_texture_from_map_data(char *line)
{
	t_texture		*tex;
	unsigned char	**elems;		

	if (!(tex = (t_texture*)malloc(sizeof(t_texture))))
		error_output("Memory allocation of t_texture struct failed\n");
	elems = ft_strsplit(line, ','); // break character should be a unique character that will not appear in any of the actual data
	tex->w = ft_atoi(elems[0]);
	tex->h = ft_atoi(elems[1]);
	tex->size = ft_atoi(elems[2]);
	tex->color_type = ft_atoi(elems[3]);
	tex->color_depth = ft_atoi(elems[4]);
	tex->format = ft_atoi(elems[5]);
	tex->bpp = ft_atoi(elems[6]);
	tex->pitch = ft_atoi(elems[7]);
	if (!(tex->map_pixels = (unsigned char *)malloc(sizeof(unsigned char) * tex->size)))
		error_output("Memory allocation of editor pixel pointer failed\n");
	ft_memcpy(tex->map_pixels, elems[8], tex->size);
	if (!(tex->pixels = (unsigned int *)malloc(sizeof(unsigned int) *
		(tex->h * tex->pitch))))
		error_output("Memory allocation of pixel pointer failed\n");
	convert_editor_tex(tex);
	free(tex->map_pixels);
	tex->map_pixels = NULL;
	free_array(elems);
	return (tex);
}
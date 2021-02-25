/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/25 15:59:24 by rzukale          ###   ########.fr       */
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
** 1st pass at loading char* and converting to uint32. Need to see text output before making further changes
** 1st index = pitch, after that comes texture height separated by ' ' followed by uint32 data
*/

unsigned int	*load_texture_from_map_data(char *line)
{
	int 	i;
	int 	pitch;
	int 	h;
	Uint32	*tex;

	pitch = ft_atoi(line);
	while (*line != ' ')
		*line++;
	h = ft_atoi(line);
	while (*line != ' ')
		*line++;
	if (!(tex = (Uint32*)malloc(sizeof(Uint32) * (pitch * h))))
		error_output("Memory allocation failed when loading texture from map data\n");
	i = 0;
	while (line[i])
	{
		tex[i] = ft_atoi(line[i]);
		i++;
	}
	return (tex);
}
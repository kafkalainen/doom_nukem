/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/01/25 16:55:10 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

Uint32	swap_channels(Uint32 color)
{
	Uint32 rgba;

	rgba = (((color & 0xFF) & 0xFF) << 16) |
		((((color >> 8)  & 0xFF) & 0xFF) << 8 )|
		(((color >> 16)  & 0xFF) & 0xFF) |
		((((color >> 24) & 0xFF) & 0xFF) << 24);
	return (rgba);
}

void	*convert_to_uint32(Uint32 *dest, SDL_Surface *image)
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

void	load_texture(char *path, t_home *home, int i)
{
	SDL_Surface		*image;

	image = IMG_Load(path);
	if (image == NULL)
		error_output("PNG image file loading failed\n");
	else
	{
		SDL_LockSurface(image);
		if (!(home->textures[i] = malloc(sizeof(Uint32) *
			(image->pitch * image->h))))
				error_output("Memory allocation failed\n");
		memory_copy(home->textures[i], image);
		SDL_UnlockSurface(image);
	}
	SDL_FreeSurface(image);
}

void	init_textures(t_home *home)
{
	load_texture("textures/greybrick.png", home, 0);
	load_texture("textures/redbrick.png", home, 1);
	load_texture("textures/wood.png", home, 2);
	load_texture("textures/eagle.png", home, 3);
}

/*
** 1st pass at loading char* and converting to uint32. Need to see text output before making further changes
** 1st index = pitch, after that comes texture height separated by ' ' followed by uint32 data
*/

Uint32	*load_texture_from_map_data(char *line)
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
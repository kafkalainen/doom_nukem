/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:02:59 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/20 17:16:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
** Open file, read everything to buffer, then go through it byte by byte
** first look for keyword "doom_textures" = textures start here
** next take nbr_of_textures
** malloc necessary number of texture points
** while loop until at nbr_of_textures
** for every texture, create a t_png and allocate the data to each point
** then inflate the compressed pixel info and convert it to pixels
** just like png_parser does
** finally transfer all data to t_texture structure
*/

int		get_next_breaker(unsigned char *buf)
{
	int i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == READ_BREAKER)
			return (i);
		i++;
	}
}

/*
** Each map data element type is separated by a element tag (eg. doom_textures for textures)
** element tag line for all elements will include element tag, total number of element components (eg. doom_textures #9)
** each element component line will include everything that specific component will need to fully initialize,
** they will be separated with a break character
** texture element example:
** [idx] [width] [height] [size] [color_type] [color_depth] [format] [bits_per_pixel] [pitch] [compressed_size] [unsigned char *pixel data]
** tex idx is determined by the order by which elements are saved into the map data file
*/

t_texture	*get_texture(unsigned char *buf, unsigned int *pos)
{
	t_texture	*tex;
	t_png		png;
	int			i;
	int			idx;

	i = -1;
	while (++i < 3)
	{
		(*pos) += get_next_breaker(buf + (*pos)) + 1;
		if (i == 0)
			idx = ft_atoi(buf + (*pos));
		else if (i == 1)
			png.source.size = ft_atoi(buf + (*pos));
		else if (i == 2)
		{
			setup_parser(&png, png.source.size);
			ft_memcpy(png.source.buf, buf + *pos, png.source.size);
			(*pos) += png.source.size;
		}
	}
	parse_png(&png);
	tex = create_texture(&png, idx);
	free_png(png);
	convert_to_uint32(tex->pixels, tex);
	return (tex);
}

void	parse_map_data(unsigned char *buf, unsigned int size, t_home *home)
{
	unsigned int	pos;
	int				i;

	pos = 0;
	buf = ft_strstr(buf, "doom_textures");
	pos += get_next_breaker(buf + pos) + 1;
	home->nbr_of_textures = ft_atoi(buf + pos);
	if (!(home->editor_tex = (t_texture**)malloc(sizeof(t_texture*) * (home->nbr_of_textures + 1))))
		error_output("failed to allocate memory to editor textures\n");
	home->editor_tex[0] = NULL;
	i = 1;
	while (i <= home->nbr_of_textures)
	{
		home->editor_tex[i] = get_texture(buf, &pos);
		i++;
	}
}

int		open_file(t_home *home, char *path)
{
	int				fd;
	unsigned char	*buf;
	unsigned int	size;

	if ((fd = OPEN_FILE(path, READ_ONLY)) < 0)
		error_output("Failed to open file\n");
	else
	{
		if (!(buf = (unsigned char *)malloc(sizeof(unsigned char) * MAX_SIZE))) // tone down the MAX_SIZE for this once we know the avg range of file sizes
			error_output("Memory allocation of source buffer failed\n");
		size = READ_FILE(fd, buf, MAX_SIZE);
		if (size <= 0)
			error_output("Failed to read file\n");
		else if (size >= MAX_SIZE)
			error_output("File is too large\n");
		if (CLOSE_FILE(fd) == -1)
			error_output("Could not close file\n");
		parse_map_data(buf, size, home);
		free(buf);
	}
	return (1);
}

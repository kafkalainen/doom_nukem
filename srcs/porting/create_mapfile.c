/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mapfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:15:57 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/26 15:17:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
** Separate functions for creating, writing to and reading from map files
** states: 0 = initialized; 1 = file creation done successfully;
** 2 = successfully wrote texture/audio/sector data to file
** [idx][width] [height] [size] [color_type] [color_depth]
** [format] [bits_per_pixel] [pitch] [compressed_size]
** [unsigned char *pixel data]
*/

unsigned char	*create_write_buffer(t_texture *tex)
{
	unsigned char	*buf;

	buf = NULL;
	buf = (unsigned char *)ft_strjoin(WRITE_BREAKER, ft_itoa(tex->idx));
	buf = (unsigned char *)ft_strjoin((const char *)buf, WRITE_BREAKER);
	buf = (unsigned char *)ft_strjoin((const char *)buf,
			ft_itoa(tex->source_size));
	buf = (unsigned char *)ft_strjoin((const char *)buf, WRITE_BREAKER);
	return (buf);
}

/*
**	// if (write(fd, "/doom_textures\n", strlen("/doom_textures\n")) == -1)
**	// 		printf("failed to add texture ending marker\n");
*/

void	write_texture_data(int fd, t_home *home)
{
	int				i;
	unsigned char	*buf;

	buf = NULL;
	buf = (unsigned char *)ft_strjoin("doom_textures #",
			(const char *)ft_itoa(home->nbr_of_textures));
	buf = (unsigned char *)ft_strjoin((const char *)buf, "\n");
	if (write(fd, buf, ft_strlen((const char *)buf)) == -1)
		printf("failed to add texture numbers\n");
	ft_strdel((char **)&buf);
	i = 1;
	while (i <= home->nbr_of_textures)
	{
		buf = create_write_buffer(home->editor_tex[i]);
		if (buf == NULL)
			printf("failed to create write buffer\n");
		if (write(fd, buf, ft_strlen((const char *)buf)) == -1)
			printf("failed to write texture\n");
		if (write(fd, home->editor_tex[i]->source,
				home->editor_tex[i]->source_size) == -1)
			printf("failed to write texture\n");
		if (write(fd, "\n", 1) == -1)
			printf("failed to write texture\n");
		ft_strdel((char **)&buf);
		i++;
	}
}

/*
**	Add writing map and audio data for the mapfile.
*/

int	create_map_file(t_home *home)
{
	int		fd;
	char	*tmp = "./map_files/test.DATA";

	doom_open(&fd, (const char **)&tmp,
		WRITE_ONLY | CREATE_FILE | TRUNCATE | CHECK_EXIST);
	if (fd < 0)
		return (-1);
	write_texture_data(fd, home);
	if (doom_close(&fd) == -1)
		return (-1);
	return (1);
}

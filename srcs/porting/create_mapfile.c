/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mapfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:15:57 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/20 17:09:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
** Separate functions for creating, writing to and reading from map files
** states: 0 = initialized; 1 = file creation done successfully; 2 = successfully wrote texture/audio/sector data to file
** [idx][width] [height] [size] [color_type] [color_depth] [format] [bits_per_pixel] [pitch] [compressed_size] [unsigned char *pixel data]
*/

unsigned char	*create_write_buffer(t_texture *tex)
{
	unsigned char	*buf;

	buf = NULL;
	buf = ft_strjoin(WRITE_BREAKER, ft_itoa(tex->idx));
	buf = ft_strjoin(buf, WRITE_BREAKER);
	buf = ft_strjoin(buf, ft_itoa(tex->source_size));
	buf = ft_strjoin(buf, WRITE_BREAKER);
	return (buf);
}

void	write_texture_data(int fd, t_home *home)
{
	int				i;
	unsigned char	*buf;

	buf = NULL;
	buf = ft_strjoin("doom_textures #", ft_itoa(home->nbr_of_textures));
	buf = ft_strjoin(buf, "\n");
	if (write(fd, buf, strlen(buf)) == -1)
			printf("failed to add texture numbers\n");
	ft_strdel(&buf);
	i = 1;
	while (i <= home->nbr_of_textures)
	{
		if ((buf = create_write_buffer(home->editor_tex[i])) == NULL)
			printf("failed to create write buffer\n");
		if (write(fd, buf, strlen(buf)) == -1)
			printf("failed to write texture\n");
		if (write(fd, home->editor_tex[i]->source, home->editor_tex[i]->source_size) == -1)
			printf("failed to write texture\n");
		if (write(fd, "\n", 1) == -1)
			printf("failed to write texture\n");
		ft_strdel(&buf);
		i++;
	}
	// if (write(fd, "/doom_textures\n", strlen("/doom_textures\n")) == -1)
	// 		printf("failed to add texture ending marker\n");
}

int		create_map_file(t_home *home)
{
	int		fd;
	char	*tmp = "./map_files/test.DATA";

	fd = OPEN_FILE(tmp, WRITE_ONLY | CREATE_FILE | TRUNCATE | CHECK_EXIST, 0644);
	if (fd < 0)
		return (-1);
	write_texture_data(fd, home);
	// write audio data
	// write sector data
	if (CLOSE_FILE(fd) == -1)
		return (-1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:23:41 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/18 16:15:00 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/png_parser.h"

void	get_current_chunk(t_chunk *chunk, unsigned char *buf, int i)
{
	ft_memcpy(chunk->length, buf + i, 4);
	chunk->size = get_big_endian(chunk->length);
	chunk->type[4] = 0;
	ft_memcpy(chunk->type, buf + i + 4, 4);
}

int		get_big_endian(unsigned char *buf)
{
	return ((buf[0] << 24) |
		(buf[1] << 16) |
		(buf[2] << 8) |
		buf[3]);
}

int		check_depth(int depth)
{
	return ((depth == 1 || depth == 2 || depth == 4 ||
		depth == 8 || depth == 16 ? 1 : 0));
}

void	check_end(t_png *png)
{
	if (png->state != 1)
		error_output("Illegal chunk order\n");
	if (png->chunk.size != 0)
		error_output("IEND chunk size must be 0\n");
	png->state = 2;
}

void	check_idat(t_png *png)
{
	if (png->chunk.size == 0 || png->state != 1)
		error_output("Illegal chunk order\n");
	png->compressed_size += png->chunk.size;
}

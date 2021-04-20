/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:32:45 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/17 15:38:49 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_png		png_parser(char *path)
{
	int			fd;
	t_png		png;

	setup_parser(&png, MAX_SIZE);
	if ((fd = OPEN_FILE(path, READ_ONLY)) < 0)
		error_output("Failed to open file\n");
	else
	{
		png.source.size = READ_FILE(fd, png.source.buf, MAX_SIZE);
		if (png.source.size <= 0)
			error_output("Failed to read file\n");
		else if (png.source.size >= MAX_SIZE)
			error_output("File is too large\n");
		if (CLOSE_FILE(fd) == -1)
			error_output("Could not close file\n");
		parse_png(&png);
	}
	return (png);
}

void		parse_data(t_png *png)
{
	t_crc crc;

	crc.flag = 0;
	while (png->i < png->source.size && png->state != 2)
	{
		get_current_chunk(&png->chunk, png->source.buf, png->i);
		verify_crc(png->source.buf + png->i + 8 + png->chunk.size,
			png->source.buf + png->i + 4, png->chunk.size + 4, &crc);
		verify_chunks(png);
		png->i += png->chunk.size + 12;
	}
	png->i = 33;
	if (!(png->compressed = (unsigned char *)malloc(sizeof(unsigned char) * png->compressed_size)))
		error_output("Memory allocation of compressed data pointer failed\n");
	while (png->i < png->source.size)
	{
		get_current_chunk(&png->chunk, png->source.buf, png->i);
		if (ft_strcmp(png->chunk.type, "IDAT") == 0)
		{
			ft_memcpy(png->compressed + png->compressed_index,
				png->source.buf + png->i + 8, png->chunk.size);
			png->compressed_index += png->chunk.size;
		}
		png->i += png->chunk.size + 12;
	}
}

void		decode_png(t_png *png)
{
	png->inflated_size = ((png->width * (png->height * png->bpp + 7)) / 8) +
		png->height;
	if (!(png->inflated = (unsigned char *)malloc(sizeof(unsigned char) * png->inflated_size)))
		error_output("Memory allocation of inflated data pointer failed\n");
	ft_inflate(png);
	convert_to_pixels(png);
}

void		setup_parser(t_png *png, unsigned int size)
{
	if (!(png->source.buf = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		error_output("Memory allocation of source buffer failed\n");
	png->state = 0;
	png->i = 8;
	png->compressed_size = 0;
	png->compressed_index = 0;
	png->inflated_size = 0;
	png->final_size = 0;
}

void		verify_chunks(t_png *png)
{
	if (ft_strcmp(png->chunk.type, "IHDR") == 0)
		check_header(png);
	else if (ft_strcmp(png->chunk.type, "IDAT") == 0)
		check_idat(png);
	else if (ft_strcmp(png->chunk.type, "IEND") == 0)
		check_end(png);
}

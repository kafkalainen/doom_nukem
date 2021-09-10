/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:19:58 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/05 15:32:43 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	parse_png(t_png *png)
{
	//validate_signature(png->source.buf);
	parse_data(png);
	decode_png(png);
}

void	free_png(t_png png)
{
	free(png.source.buf);
	free(png.compressed);
	free(png.inflated);
	free(png.pixels);
}

void	add_texture_values(t_png *png, t_texture *tex, int idx)
{
	tex->tex.width = png->width;
	tex->tex.height = png->height;
	tex->bpp = (png->depth / 8) * png->channels;
	tex->size = png->final_size;
	tex->color_depth = png->depth;
	tex->color_type = png->color_type;
	tex->format = png->format;
	tex->source_size = png->source.size;
	tex->pitch = (tex->tex.width * tex->bpp);
	tex->idx = idx;
}

void	assemble_idat_chunks(t_png *png)
{
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

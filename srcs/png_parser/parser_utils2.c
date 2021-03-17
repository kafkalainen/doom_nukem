/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:19:58 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/17 15:23:40 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	parse_png(t_png *png)
{
	validate_signature(png->source.buf);
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
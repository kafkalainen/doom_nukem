/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:22:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/20 12:21:36 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	get_texel(int x, int y, t_texture *tex)
{
	int	offset_x;
	int	offset_y;

	offset_x = x % tex->w;
	offset_y = y % tex->h;
	return ((Uint32)tex->pixels[(offset_y * tex->w) + offset_x]);
}

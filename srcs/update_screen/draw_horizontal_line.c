/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:56:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/04 16:46:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	draw_horizontal_line(Uint32 *buffer, t_texture *tex, t_steps *step, int cur_y)
{
	t_uvz	texel;
	int		cur_x;
	float	offset;
	float	offset_step;
	int		size;

	size = tex->w - 1;
	texel.u = step->start_uv.u + 0.4;
	texel.v = step->start_uv.v + 0.2;
	offset_step = 1.0f / ((float)(step->end_x - step->start_x));
	offset = 0.0f;
	cur_x = step->start_x;
	while (cur_x < step->end_x)
	{
		// 6 FPS
		// texel.u = (1.0f - offset) * step->start_uv.u + offset * step->end_uv.u;
		// texel.v = (1.0f - offset) * step->start_uv.v + offset * step->end_uv.v;
		// texel.w = (1.0f - offset) * step->start_uv.w + offset * step->end_uv.w;
		// texel = texel_inv_z(texel);
		put_pixel(buffer, cur_x, cur_y,
			get_texel(
				&(t_uv){texel.u * size, texel.v * size},
				&(t_uv){tex->w, tex->h}, tex->pixels));
		offset += offset_step;
		cur_x++;
	}
	return (TRUE);
}

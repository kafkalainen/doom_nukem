/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:56:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/08 14:45:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	draw_horizontal_line(Uint32 *buffer, float *depth_buffer,
	t_texel *tex, t_steps *step)
{
	t_uvz	texel;
	int		cur_x;
	float	offset;
	float	offset_step;
	int		size;

	offset = 0.0f;
	size = tex->width - 1;
	cur_x = step->start_x;
	texel = step->start_uv;
	offset_step = 1.0f / ((float)(step->end_x - step->start_x));
	if (step->end_x < 0 || step->cur_y > SCREEN_HEIGHT || step->cur_y < 0)
		return (FALSE);
	while (cur_x < step->end_x)
	{
		texel.u = (1.0f - offset) * step->start_uv.u + offset * step->end_uv.u;
		texel.v = (1.0f - offset) * step->start_uv.v + offset * step->end_uv.v;
		texel.w = (1.0f - offset) * step->start_uv.w + offset * step->end_uv.w;
		if (texel.w > depth_buffer[cur_x + step->cur_y * SCREEN_WIDTH])
		{
			texel = texel_inv_z(texel);
			put_pixel(buffer, cur_x, step->cur_y,
				get_texel(
					&(t_uv){texel.u * size, texel.v * size},
					&(t_uv){tex->width, tex->height}, tex->texels));
			depth_buffer[cur_x + step->cur_y * SCREEN_WIDTH] = texel.w;
		}
		offset += offset_step;
		cur_x++;
	}
	return (TRUE);
}

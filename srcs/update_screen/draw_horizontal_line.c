/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:56:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/23 13:26:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calc_texel(t_uvz *texel, t_uvz *start, float offset,
					t_uvz *end)
{
	texel->u = (1.0f - offset) * start->u + offset * end->u;
	texel->v = (1.0f - offset) * start->v + offset * end->v;
	texel->w = (1.0f - offset) * start->w + offset * end->w;
}

int	draw_horizontal_line(Uint32 *buffer, float *depth_buffer, t_texel *tex,
	t_steps *step)
{
	t_uvz	texel;
	int		cur_x;
	float	offset;
	float	offset_step;

	offset = 0.0f;
	cur_x = step->start_x;
	texel = step->start_uv;
	offset_step = 1.0f / ((float)(step->end_x - step->start_x));
	if (step->start_x < 0 || step->cur_y > SCREEN_HEIGHT - 1
		|| step->cur_y < 0 || step->end_x > SCREEN_WIDTH - 1)
		return (FALSE);
	while (cur_x < step->end_x)
	{
		calc_texel(&texel, &step->start_uv, offset, &step->end_uv);
		if (texel.w > depth_buffer[cur_x + step->cur_y * SCREEN_WIDTH])
		{
			texel = texel_inv_z(texel);
			put_pixel(buffer, cur_x, step->cur_y,
				get_texel(
					&(t_uv){texel.u * tex->width - 1, texel.v * tex->height - 1},
					&(t_uv){tex->width, tex->height}, tex->texels));
			depth_buffer[cur_x + step->cur_y * SCREEN_WIDTH] = texel.w;
		}
		offset += offset_step;
		cur_x++;
	}
	return (TRUE);
}

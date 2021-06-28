/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:56:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/28 11:27:50 by jnivala          ###   ########.fr       */
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


static void	calc_illumination(float *illumination, float *start, float offset,
					float *end)
{
	*illumination = (1.0f - offset) * *start + offset * *end;
}


/*
**	variable cur_x to be removed
*/
int	draw_horizontal_line(Uint32 *buffer, float *depth_buffer, t_texel *tex,
	t_steps *step)
{
	t_uvz	texel;
	float	illumination;
	float	offset;
	float	offset_step;

	offset = 0.0f;
	texel = step->start_uv;
	illumination = step->start_i;
	offset_step = 1.0f / ((float)(step->end_x - step->start_x));
	if (step->start_x < 0 || step->cur_y > SCREEN_HEIGHT - 1
		|| step->cur_y < 0 || step->end_x > SCREEN_WIDTH - 1)
		return (FALSE);
	while (step->start_x < step->end_x)
	{
		calc_texel(&texel, &step->start_uv, offset, &step->end_uv);
		calc_illumination(&illumination, &step->start_i, offset, &step->end_i);
		if (texel.w > depth_buffer[step->start_x + step->cur_y * SCREEN_WIDTH])
		{
			depth_buffer[step->start_x + step->cur_y * SCREEN_WIDTH] = texel.w;
			texel = texel_inv_z(texel);
			put_pixel(buffer, step->start_x, step->cur_y,
				colour_scale(
					get_texel(
					&(t_uv){texel.u * tex->width - 1, texel.v * tex->height - 1},
					&(t_uv){tex->width, tex->height}, tex->texels)
					// );
					, illumination));
		}
		offset += offset_step;
		step->start_x++;
	}
	return (TRUE);
}

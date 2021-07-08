/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:56:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/08 15:32:02 by jnivala          ###   ########.fr       */
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


static void	calc_lumel(float *lumel, float *start, float offset, float *end)
{
	*lumel = (1.0f - offset) * *start + offset * *end;
}

static Uint32	check_for_valid_range(t_steps *step)
{
	if (step->start_x < 0 || step->cur_y > SCREEN_HEIGHT - 1
		|| step->cur_y < 0 || step->end_x > SCREEN_WIDTH - 1
		|| step->start_x >= step->end_x)
		return (FALSE);
	else
		return (TRUE);
}


void	draw_segment(Uint32 *buffer, float *depth_buffer, t_texel *tex, t_steps *step)
{
	t_uvz	texel;
	float	lumel;

	calc_texel(&texel, &step->start_uv, step->offset, &step->end_uv);
	calc_lumel(&lumel, &step->start_lu, step->offset, &step->end_lu);
	if (texel.w > depth_buffer[step->start_x + step->cur_y * SCREEN_WIDTH])
	{
		depth_buffer[step->start_x + step->cur_y * SCREEN_WIDTH] = texel.w;
		texel = texel_inv_z(texel);
		put_pixel(buffer, step->start_x, step->cur_y,
			colour_scale(
				get_texel(
					&(t_uv){texel.u * tex->width - 1, texel.v * tex->height - 1},
					&(t_uv){tex->width, tex->height}, tex->texels)
					, lumel));
	}
	step->offset += step->offset_step;
	step->start_x++;
}

int	draw_horizontal_line(Uint32 *buffer, float *depth_buffer, t_texel *tex,
	t_steps *step)
{
	int		pixels;

	step->offset = 0.0f;
	step->offset_step = 1.0f / ((float)(step->end_x - step->start_x));
	if (!check_for_valid_range(step))
		return (FALSE);
	pixels = step->end_x - step->start_x;
	while (pixels--)
	{
		draw_segment(buffer, depth_buffer, tex, step);
	}
	return (TRUE);
}

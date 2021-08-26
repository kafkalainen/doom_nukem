/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:56:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/26 13:13:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static Uint32	check_for_valid_range(t_steps *step)
{
	if (step->start_x < 0 || step->cur_y > SCREEN_HEIGHT - 1
		|| step->cur_y < 0 || step->end_x > SCREEN_WIDTH - 1
		|| step->start_x >= step->end_x)
		return (FALSE);
	else
		return (TRUE);
}

void	draw_segment(Uint32 *buffer, float *depth_buffer, t_texel *tex,
	t_steps *step)
{
	float	lumel;
	Uint32	colour;

	while (step->sub_pixels--)
	{
		if (step->texel_inv.w > depth_buffer[step->start_x + step->cur_y
				 * SCREEN_WIDTH])
		{
			colour = get_texel(
					&(t_uv){step->texel_start.u * tex->width - 1,
					step->texel_start.v * tex->height - 1},
					&(t_uv){tex->width, tex->height}, tex->texels);
			if (colour >> 24 > 0)
			{
				calc_lumel(&lumel, &step->start_lu, step->offset,
					&step->end_lu);
				depth_buffer[step->start_x + step->cur_y * SCREEN_WIDTH]
					= step->texel_inv.w;
				put_pixel(buffer, step->start_x, step->cur_y,
					colour_scale(colour, lumel));
			}
		}
		step->texel_start = texel_add(&step->texel_start, &step->delta);
		step->start_x++;
	}
}

static void	draw_remainder(Uint32 *buffer, float *depth_buffer, t_texel *tex,
	t_steps *step)
{
	float	denom_sub;
	float	w;

	denom_sub = 1.0f / step->sub_pixels;
	w = step->texel_inv.w;
	step->offset_step = step->offset_step * step->sub_pixels * DENOMSUBDIV;
	step->offset += step->offset_step;
	calc_texel(&step->texel_inv, &step->start_uv,
		step->offset, &step->end_uv);
	step->texel_end = texel_inv_z(step->texel_inv);
	step->delta.u = (step->texel_end.u - step->texel_start.u) * denom_sub;
	step->delta.v = (step->texel_end.v - step->texel_start.v) * denom_sub;
	step->texel_inv.w = (w + step->texel_inv.w) * 0.5f;
	draw_segment(buffer, depth_buffer, tex, step);
}

static void	draw_subdiv(Uint32 *buffer, float *depth_buffer, t_texel *tex,
	t_steps *step)
{
	float	w;

	step->offset += step->offset_step;
	w = step->texel_inv.w;
	calc_texel(&step->texel_inv, &step->start_uv,
		step->offset, &step->end_uv);
	step->texel_end = texel_inv_z(step->texel_inv);
	step->delta.u = (step->texel_end.u - step->texel_start.u) * DENOMSUBDIV;
	step->delta.v = (step->texel_end.v - step->texel_start.v) * DENOMSUBDIV;
	step->texel_inv.w = (w + step->texel_inv.w) * 0.5f;
	step->sub_pixels = SUBDIV;
	draw_segment(buffer, depth_buffer, tex, step);
	step->texel_start = step->texel_end;
}

int	draw_horizontal_line(Uint32 *buffer, float *depth_buffer, t_texel *tex,
	t_steps *step)
{
	int		pixels;

	step->offset = 0.0f;
	step->offset_step = 1.0f / ((float)(step->end_x - step->start_x)) * SUBDIV;
	if (!check_for_valid_range(step))
		return (FALSE);
	pixels = step->end_x - step->start_x;
	calc_texel(&step->texel_inv, &step->start_uv, step->offset, &step->end_uv);
	step->texel_start = texel_inv_z(step->texel_inv);
	while (pixels >= SUBDIV)
	{
		draw_subdiv(buffer, depth_buffer, tex, step);
		pixels -= SUBDIV;
	}
	step->sub_pixels = pixels;
	if (pixels > 0)
		draw_remainder(buffer, depth_buffer, tex, step);
	return (TRUE);
}

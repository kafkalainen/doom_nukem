/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:56:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/03 16:42:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static Uint32	set_colour(t_steps *step, t_buffer *buffer, t_texel *tex,
				Uint32 colour)
{
	if (tex->type == space)
		return (colour_scale(colour, step->lu_start, buffer->lightness, 1));
	else
		return (colour_scale(colour, step->lu_start, buffer->lightness,
				1 / step->texel_start.w));
}

void	draw_segment(t_buffer *buffer, float *depth_buffer, t_texel *tex,
	t_steps *step)
{
	Uint32	c;

	while (step->sub_pixels--)
	{
		if (step->texel_inv.w > depth_buffer[step->start.x + step->start.y
				 * SCREEN_WIDTH])
		{
			c = get_texel(&(t_uv){step->texel_start.u * tex->width - 1,
					step->texel_start.v * tex->height - 1},
					&(t_uv){tex->width, tex->height}, tex->texels);
			if (c >> 24 > 0)
			{
				depth_buffer[step->start.x + step->start.y * SCREEN_WIDTH]
					= step->texel_inv.w;
				c = set_colour(step, buffer, tex, c);
				put_pixel(buffer, step->start, c);
			}
		}
		step->lu_start += step->delta_lu;
		step->texel_start = texel_add(&step->texel_start, &step->delta);
		step->start.x++;
	}
}

static void	draw_remainder(t_buffer *buffer, float *depth_buffer, t_texel *tex,
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
	calc_lumel(&step->lu_end, &step->start_lu, step->offset, &step->end_lu);
	step->delta.u = (step->texel_end.u - step->texel_start.u) * denom_sub;
	step->delta.v = (step->texel_end.v - step->texel_start.v) * denom_sub;
	step->delta.w = (step->texel_end.w - step->texel_start.w) * denom_sub;
	step->delta_lu = (step->lu_end - step->lu_start) * denom_sub;
	step->texel_inv.w = (w + step->texel_inv.w) * 0.5f;
	draw_segment(buffer, depth_buffer, tex, step);
}

static void	draw_subdiv(t_buffer *buffer, float *depth_buffer, t_texel *tex,
	t_steps *step)
{
	float	w;

	step->offset += step->offset_step;
	w = step->texel_inv.w;
	calc_texel(&step->texel_inv, &step->start_uv,
		step->offset, &step->end_uv);
	step->texel_end = texel_inv_z(step->texel_inv);
	calc_lumel(&step->lu_end, &step->start_lu, step->offset, &step->end_lu);
	step->delta.u = (step->texel_end.u - step->texel_start.u) * DENOMSUBDIV;
	step->delta.v = (step->texel_end.v - step->texel_start.v) * DENOMSUBDIV;
	step->delta.w = (step->texel_end.w - step->texel_start.w) * DENOMSUBDIV;
	step->delta_lu = (step->lu_end - step->lu_start) * DENOMSUBDIV;
	step->texel_inv.w = (w + step->texel_inv.w) * 0.5f;
	step->sub_pixels = SUBDIV;
	draw_segment(buffer, depth_buffer, tex, step);
	step->texel_start = step->texel_end;
	step->lu_start = step->lu_end;
}

void	draw_horizontal_line(t_buffer *buffer, float *depth_buffer,
		t_texel *tex, t_steps *step)
{
	int		pixels;

	step->offset = 0.0f;
	step->offset_step = 1.0f / ((float)(step->end.x - step->start.x)) * SUBDIV;
	if (!check_for_valid_draw_range(step))
		return ;
	pixels = step->end.x - step->start.x;
	calc_texel(&step->texel_inv, &step->start_uv, step->offset, &step->end_uv);
	step->texel_start = texel_inv_z(step->texel_inv);
	calc_lumel(&step->lu_start, &step->start_lu, step->offset, &step->end_lu);
	while (pixels >= SUBDIV)
	{
		draw_subdiv(buffer, depth_buffer, tex, step);
		pixels -= SUBDIV;
	}
	step->sub_pixels = pixels;
	if (pixels > 0)
		draw_remainder(buffer, depth_buffer, tex, step);
}

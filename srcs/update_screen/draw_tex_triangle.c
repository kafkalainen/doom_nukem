/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:25:51 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/11 13:03:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_deltas	calculate_vertex_delta(t_xyz p0, t_xyz p1,
	t_uvz uv0, t_uvz uv1)
{
	t_deltas	delta;

	delta.y = (int)p1.y - (int)p0.y;
	delta.x = (int)p1.x - (int)p0.x;
	delta.v = uv1.v - uv0.v;
	delta.u = uv1.u - uv0.u;
	delta.w = uv1.w - uv0.w;
	return (delta);
}

/*
**	Since denominators are initialized to zero, we can safely multiply them.
*/
static void	initialize_steps(t_xyz *step_side, t_uvz *tex_step_side,
	t_deltas *delta, float denom)
{
	step_side->x = delta->x * denom;
	tex_step_side->u = delta->u * denom;
	tex_step_side->v = delta->v * denom;
	tex_step_side->w = delta->w * denom;
}

/*
**	Typecasted triangle to int, and then back to float.
*/
static void	calc_current_step(t_triangle *tri, t_steps *steps, int cur_y)
{
	float		temp[2];

	temp[0] = (float)(cur_y - (int)tri->p[0].y);
	steps->start_x = tri->p[0].x + temp[0] * steps->screen_step_a_side.x;
	steps->end_x = tri->p[0].x + temp[0] * steps->screen_step_b_side.x;
	steps->start_uv.u = tri->uv[0].u + temp[0] * steps->tex_a_side.u;
	steps->start_uv.v = tri->uv[0].v + temp[0] * steps->tex_a_side.v;
	steps->start_uv.w = tri->uv[0].w + temp[0] * steps->tex_a_side.w;
	steps->end_uv.u = tri->uv[0].u + temp[0] * steps->tex_b_side.u;
	steps->end_uv.v = tri->uv[0].v + temp[0] * steps->tex_b_side.v;
	steps->end_uv.w = tri->uv[0].w + temp[0] * steps->tex_b_side.w;
	if (steps->current_triangle != 'a')
	{
		temp[1] = (float)(cur_y - (int)tri->p[1].y);
		steps->start_x = tri->p[1].x + temp[1]
			* steps->screen_step_a_side.x;
		steps->start_uv.u = tri->uv[1].u + temp[1]
			* steps->tex_a_side.u;
		steps->start_uv.v = tri->uv[1].v + temp[1]
			* steps->tex_a_side.v;
		steps->start_uv.w = tri->uv[1].w + temp[1]
			* steps->tex_a_side.w;
	}
	swap_sides(steps);
}

/*
**	Switched to delta instead of denominator.
*/
static void	draw_triangle(Uint32 *buffer, float *depth_buffer, t_triangle *triangle,
	t_texel *tex, t_steps *step)
{
	int	max_y;

	if (!step->delta_p0p1.y)
		return ;
	initialize_steps(&step->screen_step_a_side, &step->tex_a_side,
		&step->delta_p0p1, step->denom_dy_a_side);
	initialize_steps(&step->screen_step_b_side, &step->tex_b_side,
		&step->delta_p0p2, step->denom_dy_b_side);
	if (step->current_triangle == 'a')
	{
		step->cur_y = (int)triangle->p[0].y;
		max_y = (int)triangle->p[1].y;
	}
	else
	{
		step->cur_y = (int)triangle->p[1].y;
		max_y = (int)triangle->p[2].y;
	}
	while (step->cur_y <= max_y)
	{
		calc_current_step(triangle, step, step->cur_y);
		draw_horizontal_line(buffer, depth_buffer, tex, step);
		step->cur_y += 1;
	}
}

int	draw_tex_triangle(Uint32 *buffer, float *depth_buffer, t_triangle *triangle, t_texel *tex)
{
	t_steps		step;

	sort_vertices(triangle);
	step.delta_p0p1 = calculate_vertex_delta(triangle->p[0],
		triangle->p[1], triangle->uv[0], triangle->uv[1]);
	step.delta_p0p2 = calculate_vertex_delta(triangle->p[0],
		triangle->p[2], triangle->uv[0], triangle->uv[2]);
	step.denom_dy_a_side = 0;
	step.denom_dy_b_side = 0;
	if ((step.delta_p0p1.y == 0 && step.delta_p0p2.y == 0)
		|| (step.delta_p0p1.x == 0 && step.delta_p0p2.x == 0))
		return (FALSE);
	if (step.delta_p0p1.y)
		step.denom_dy_a_side = (float)fabsf(1.0f / step.delta_p0p1.y);
	if (step.delta_p0p2.y)
		step.denom_dy_b_side = (float)fabsf(1.0f / step.delta_p0p2.y);
	step.current_triangle = 'a';
	draw_triangle(buffer, depth_buffer, triangle, tex, &step);
	step.delta_p0p1 = calculate_vertex_delta(triangle->p[1],
		triangle->p[2], triangle->uv[1], triangle->uv[2]);
	step.denom_dy_a_side = 0;
	if (step.delta_p0p1.y)
		step.denom_dy_a_side = (float)fabsf(1.0f / step.delta_p0p1.y);
	step.current_triangle = 'b';
	draw_triangle(buffer, depth_buffer, triangle, tex, &step);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:25:51 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/08 15:28:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calculate_vertex_delta(t_triangle *triangle, t_deltas *delta_a,
	t_deltas *delta_b, char side)
{
	if (side == 'a')
	{
		delta_a->y = (int)triangle->p[1].y - (int)triangle->p[0].y;
		delta_a->x = (int)triangle->p[1].x - (int)triangle->p[0].x;
		delta_a->v = triangle->uv[1].v - triangle->uv[0].v;
		delta_a->u = triangle->uv[1].u - triangle->uv[0].u;
		delta_a->w = triangle->uv[1].w - triangle->uv[0].w;
		delta_a->i = triangle->lu[1] - triangle->lu[0];
	}
	else
	{
		delta_a->y = (int)triangle->p[2].y - (int)triangle->p[1].y;
		delta_a->x = (int)triangle->p[2].x - (int)triangle->p[1].x;
		delta_a->v = triangle->uv[2].v - triangle->uv[1].v;
		delta_a->u = triangle->uv[2].u - triangle->uv[1].u;
		delta_a->w = triangle->uv[2].w - triangle->uv[1].w;
		delta_a->i = triangle->lu[2] - triangle->lu[1];
	}
	delta_b->y = (int)triangle->p[2].y - (int)triangle->p[0].y;
	delta_b->x = (int)triangle->p[2].x - (int)triangle->p[0].x;
	delta_b->v = triangle->uv[2].v - triangle->uv[0].v;
	delta_b->u = triangle->uv[2].u - triangle->uv[0].u;
	delta_b->w = triangle->uv[2].w - triangle->uv[0].w;
	delta_b->i = triangle->lu[2] - triangle->lu[0];
}

/*
**	Since denominators are initialized to zero, we can safely multiply them.
*/
static void	initialize_steps(t_steps *steps, float denom_a, float denom_b)
{
	steps->screen_step_a_side.x = steps->delta_p0p1.x * denom_a;
	steps->tex_a_side.u = steps->delta_p0p1.u * denom_a;
	steps->tex_a_side.v = steps->delta_p0p1.v * denom_a;
	steps->tex_a_side.w = steps->delta_p0p1.w * denom_a;
	steps->lumel_step_a_side = steps->delta_p0p1.i * denom_a;
	steps->screen_step_b_side.x = steps->delta_p0p2.x * denom_b;
	steps->tex_b_side.u = steps->delta_p0p2.u * denom_b;
	steps->tex_b_side.v = steps->delta_p0p2.v * denom_b;
	steps->tex_b_side.w = steps->delta_p0p2.w * denom_b;
	steps->lumel_step_b_side = steps->delta_p0p2.i * denom_b;
	steps->subdiv_tex_a_side = texel_mul(&steps->tex_a_side, SUBDIVSIZE);
	steps->subdiv_tex_b_side = texel_mul(&steps->tex_b_side, SUBDIVSIZE);
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
	steps->start_uv = texel_lerp(&tri->uv[0], temp[0], &steps->tex_a_side);
	steps->start_lu = tri->lu[0] + temp[0] * steps->lumel_step_a_side;
	steps->end_uv = texel_lerp(&tri->uv[0], temp[0], &steps->tex_b_side);
	steps->end_lu = tri->lu[0] + temp[0] * steps->lumel_step_b_side;
	if (steps->current_triangle != 'a')
	{
		temp[1] = (float)(cur_y - (int)tri->p[1].y);
		steps->start_x = tri->p[1].x + temp[1]
			* steps->screen_step_a_side.x;
		steps->start_uv = texel_lerp(&tri->uv[1],
			temp[1], &steps->tex_a_side);
		steps->start_lu = tri->lu[1] + temp[1]
			* steps->lumel_step_a_side;
	}
	swap_sides(steps);
}

/*
**	Switched to delta instead of denominator.
*/
static void	draw_triangle(t_draw_data *data,
	t_triangle *triangle, t_texel *tex, t_steps *step)
{
	int	max_y;

	if (!step->delta_p0p1.y)
		return ;
	initialize_steps(step, step->denom_dy_a_side, step->denom_dy_b_side);
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
		draw_horizontal_line(data->buffer, data->depth_buffer, tex, step);
		step->cur_y += 1;
	}
}

int	draw_tex_triangle(Uint32 *buffer, float *depth_buffer,
	t_triangle *triangle, t_texel *tex)
{
	t_steps		step;
	t_draw_data	data;

	sort_vertices(triangle);
	data.buffer = buffer;
	data.depth_buffer = depth_buffer;
	calculate_vertex_delta(triangle, &step.delta_p0p1, &step.delta_p0p2, 'a');
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
	draw_triangle(&data, triangle, tex, &step);
	calculate_vertex_delta(triangle, &step.delta_p0p1, &step.delta_p0p2, 'b');
	step.denom_dy_a_side = 0;
	if (step.delta_p0p1.y)
		step.denom_dy_a_side = (float)fabsf(1.0f / step.delta_p0p1.y);
	step.current_triangle = 'b';
	draw_triangle(&data, triangle, tex, &step);
	return (TRUE);
}

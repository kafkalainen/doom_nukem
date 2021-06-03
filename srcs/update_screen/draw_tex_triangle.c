/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:25:51 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/03 08:41:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"
#include <pthread.h>
#include <stdlib.h>

static t_deltas	calculate_vertex_delta(t_xyz p0, t_xyz p1,
	t_uvz uv0, t_uvz uv1)
{
	t_deltas	delta;

	delta.y = p1.y - p0.y;
	delta.x = p1.x - p0.x;
	delta.v = uv1.v - uv0.v;
	delta.u = uv1.u - uv0.u;
	delta.w = uv1.w - uv0.w;
	return (delta);
}

static void	initialize_steps(t_xyz *step_side, t_uvz *tex_step_side,
	t_deltas *delta, float *denom)
{
	step_side->x = 0;
	tex_step_side->u = 0.0f;
	tex_step_side->v = 0.0f;
	tex_step_side->w = 0.0f;
	if (*denom)
	{
		step_side->x = delta->x * *denom;
		tex_step_side->u = delta->u * *denom;
		tex_step_side->v = delta->v * *denom;
		tex_step_side->w = delta->w * *denom;
	}
}

static void	calc_current_step(t_triangle *tri, t_steps *steps)
{
	float		temp[2];

	temp[0] = steps->cur_y - tri->p[0].y;
	steps->start_x = tri->p[0].x + (float)temp[0] * steps->screen_step_a_side.x;
	steps->end_x = tri->p[0].x + (float)temp[0] * steps->screen_step_b_side.x;
	steps->start_uv.u = tri->uv[0].u + (float)temp[0] * steps->tex_a_side.u;
	steps->start_uv.v = tri->uv[0].v + (float)temp[0] * steps->tex_a_side.v;
	steps->start_uv.w = tri->uv[0].w + (float)temp[0] * steps->tex_a_side.w;
	steps->end_uv.u = tri->uv[0].u + (float)temp[0] * steps->tex_b_side.u;
	steps->end_uv.v = tri->uv[0].v + (float)temp[0] * steps->tex_b_side.v;
	steps->end_uv.w = tri->uv[0].w + (float)temp[0] * steps->tex_b_side.w;
	if (steps->current_triangle != 'a')
	{
		temp[1] = steps->cur_y - tri->p[1].y;
		steps->start_x = tri->p[1].x + (float)temp[1]
			* steps->screen_step_a_side.x;
		steps->start_uv.u = tri->uv[1].u + (float)temp[1]
			* steps->tex_a_side.u;
		steps->start_uv.v = tri->uv[1].v + (float)temp[1]
			* steps->tex_a_side.v;
		steps->start_uv.w = tri->uv[1].w + (float)temp[1]
			* steps->tex_a_side.w;
	}
	swap_sides(steps);
}

static void *draw_area(void *args)
{
	int			start_y;
	int			max_y;
	int			index;
	t_arg		*arg;
	t_steps		thread_steps;
	pthread_t	current;


	arg = (t_arg*)args;
	index = 0;
	current = pthread_self;
	thread_steps = *(arg->step);
	while (current != arg->tid[index])
		index++;
	start_y = index * arg->step->thread_step
		+ arg->step->cur_y;
	start_y = (index + 1) * arg->step->thread_step
		+ arg->step->max_y;
	while (start_y <= max_y)
	{
		calc_current_step(arg->triangle, &thread_steps);
		draw_horizontal_line(arg->buffer, arg->tex, &thread_steps);
		start_y++;
	}
	return (NULL);
}

static void	draw_triangle(Uint32 *buffer, t_triangle *triangle,
	t_texture *tex, t_steps *step)
{
	int		i;
	int		max_y;
	t_arg	args;

	args.tex = tex;
	args.step = step;
	args.triangle = triangle;
	args.buffer = buffer;
	initialize_steps(&step->screen_step_a_side, &step->tex_a_side,
		&step->delta_p0p1, &step->denom_dy_a_side);
	initialize_steps(&step->screen_step_b_side, &step->tex_b_side,
		&step->delta_p0p2, &step->denom_dy_b_side);
	if (!step->denom_dy_a_side)
		return ;
	if (step->current_triangle == 'a')
	{
		step->cur_y = (int)triangle->p[0].y;
		step->max_y = (int)triangle->p[1].y;
	}
	else
	{
		step->cur_y = (int)triangle->p[1].y;
		step->max_y = (int)triangle->p[2].y;
	}
	step->thread_step = (step->max_y - step->cur_y) / MAX_THREADS;
	while (i < MAX_THREADS)
	{
		pthread_create(&args.tid[i], NULL, &draw_area, (void*)&args);
		i++;
	}
	while (i--)
		pthread_join(args.tid[i], NULL);
}

int	draw_tex_triangle(Uint32 *buffer, t_triangle *triangle, t_texture *tex)
{
	t_steps		step;

	sort_vertices(triangle);
	step.delta_p0p1 = calculate_vertex_delta(triangle->p[0],
		triangle->p[1], triangle->uv[0], triangle->uv[1]);
	step.delta_p0p2 = calculate_vertex_delta(triangle->p[0],
		triangle->p[2], triangle->uv[0], triangle->uv[2]);
	step.denom_dy_a_side = 0;
	step.denom_dy_b_side = 0;
	if (step.delta_p0p1.y)
		step.denom_dy_a_side = (float)fabsf(1.0f / step.delta_p0p1.y);
	if (step.delta_p0p2.y)
		step.denom_dy_b_side = (float)fabsf(1.0f / step.delta_p0p2.y);
	step.current_triangle = 'a';
	draw_triangle(buffer, triangle, tex, &step);
	step.delta_p0p1 = calculate_vertex_delta(triangle->p[1],
		triangle->p[2], triangle->uv[1], triangle->uv[2]);
	step.denom_dy_a_side = 0;
	if (step.delta_p0p1.y)
		step.denom_dy_a_side = (float)fabsf(1.0f / step.delta_p0p1.y);
	step.current_triangle = 'b';
	draw_triangle(buffer, triangle, tex, &step);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:25:51 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/30 17:51:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_deltas	calculate_vertex_delta(t_xyz p0, t_xyz p1, t_uvz uv0, t_uvz uv1)
{
	t_deltas	delta;

	delta.y = p1.y - p0.y;
	delta.x = p1.x - p0.x;
	delta.v = uv1.v - uv0.v;
	delta.u = uv1.u - uv0.u;
	delta.w = uv1.w - uv0.w;
	return (delta);
}

void	initialize_steps(t_xyz *step_side, t_uvz *tex_step_side, t_deltas *delta, float *denom)
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

static void	calc_current_step(t_triangle *tri, t_steps *steps, char choice)
{
	float		temp[2];

	if (choice == 'a')
	{
		temp[0] = steps->cur_y - tri->p[0].y;
		steps->start_x = tri->p[0].x + (float)temp[0] * steps->screen_step_a_side.x;
		steps->end_x = tri->p[0].x + (float)temp[0] * steps->screen_step_b_side.x;
		steps->start_uv.u = tri->uv[0].u + (float)temp[0] * steps->tex_step_a_side.u;
		steps->start_uv.v = tri->uv[0].v + (float)temp[0] * steps->tex_step_a_side.v;
		steps->start_uv.w = tri->uv[0].w + (float)temp[0] * steps->tex_step_a_side.w;
		steps->end_uv.u = tri->uv[0].u + (float)temp[0] * steps->tex_step_b_side.u;
		steps->end_uv.v = tri->uv[0].v + (float)temp[0] * steps->tex_step_b_side.v;
		steps->end_uv.w = tri->uv[0].w + (float)temp[0] * steps->tex_step_b_side.w;
	}
	else
	{
		temp[0] = steps->cur_y - tri->p[0].y;
		temp[1] = steps->cur_y - tri->p[1].y;
		steps->start_x = tri->p[1].x + (float)temp[1] * steps->screen_step_a_side.x;
		steps->end_x = tri->p[0].x + (float)temp[0] * steps->screen_step_b_side.x;
		steps->start_uv.u = tri->uv[1].u + (float)temp[1] * steps->tex_step_a_side.u;
		steps->start_uv.v = tri->uv[1].v + (float)temp[1] * steps->tex_step_a_side.v;
		steps->start_uv.w = tri->uv[1].w + (float)temp[1] * steps->tex_step_a_side.w;
		steps->end_uv.u = tri->uv[0].u + (float)temp[0] * steps->tex_step_b_side.u;
		steps->end_uv.v = tri->uv[0].v + (float)temp[0] * steps->tex_step_b_side.v;
		steps->end_uv.w = tri->uv[0].w + (float)temp[0] * steps->tex_step_b_side.w;
	}
	if (steps->start_x > steps->end_x)
	{
		swap_int(&steps->start_x, &steps->end_x);
		swap_uvz(&steps->start_uv, &steps->end_uv);
	}
}

int	draw_horizontal_line(t_frame *frame, t_texture *tex, t_steps *step)
{
	t_uvz	texel;
	int		cur_x;
	float	offset;
	float	offset_step;

	texel = step->start_uv;
	offset_step = 1.0f / ((float)(step->end_x - step->start_x));
	offset = 0.0f;
	cur_x = step->start_x;
	while (cur_x < step->end_x)
	{
		texel.u = (1.0f - offset) * step->start_uv.u + offset * step->end_uv.u;
		texel.v = (1.0f - offset) * step->start_uv.v + offset * step->end_uv.v;
		texel.w = (1.0f - offset) * step->start_uv.w + offset * step->end_uv.w;
		texel = texel_inv_z(texel);
		put_pixel(frame->buffer, cur_x, step->cur_y,
			get_texel(texel.u * tex->w, texel.v * tex->h, tex));
		offset += offset_step;
		cur_x++;
	}
	return (TRUE);
}

int	draw_tex_triangle(t_frame *frame, t_triangle *triangle, t_texture *tex)
{
	t_deltas	delta_p0p1;
	t_deltas	delta_p0p2;
	t_steps		step;

	sort_vertices(triangle);
	delta_p0p1 = calculate_vertex_delta(triangle->p[0], triangle->p[1], triangle->uv[0], triangle->uv[1]);
	delta_p0p2 = calculate_vertex_delta(triangle->p[0], triangle->p[2], triangle->uv[0], triangle->uv[2]);
	if (delta_p0p1.y)
		step.denom_dy_a_side = (float)fabsf(1.0f / delta_p0p1.y);
	else
		step.denom_dy_a_side = 0;
	if (delta_p0p1.y)
		step.denom_dy_b_side = (float)fabsf(1.0f / delta_p0p2.y);
	else
		step.denom_dy_b_side = 0;
	initialize_steps(&step.screen_step_a_side, &step.tex_step_a_side, &delta_p0p1, &step.denom_dy_a_side);
	initialize_steps(&step.screen_step_b_side, &step.tex_step_b_side, &delta_p0p2, &step.denom_dy_b_side);
	if (step.denom_dy_a_side)
	{
		step.cur_y = (int)triangle->p[0].y;
		while (step.cur_y <= (int)triangle->p[1].y)
		{
			calc_current_step(triangle, &step, 'a');
			draw_horizontal_line(frame, tex, &step);
			step.cur_y++;
		}
	}
	delta_p0p1 = calculate_vertex_delta(triangle->p[1], triangle->p[2], triangle->uv[1], triangle->uv[2]);
	if (delta_p0p1.y)
		step.denom_dy_a_side = (float)fabsf(1.0f / delta_p0p1.y);
	else
		step.denom_dy_a_side = 0;
	if (step.denom_dy_a_side)
	{
		initialize_steps(&step.screen_step_a_side, &step.tex_step_a_side, &delta_p0p1, &step.denom_dy_a_side);
		initialize_steps(&step.screen_step_b_side, &step.tex_step_b_side, &delta_p0p2, &step.denom_dy_b_side);
		step.cur_y = triangle->p[1].y;
		while (step.cur_y <= (int)triangle->p[2].y)
		{
			calc_current_step(triangle, &step, 'b');
			draw_horizontal_line(frame, tex, &step);
			step.cur_y++;
		}
	}
	return (TRUE);
}

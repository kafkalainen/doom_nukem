/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_polygon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:35:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/27 20:24:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	swap_xyz(t_xyz *p0, t_xyz *p1)
{
	t_xyz	swap;

	swap.x = p0->x;
	swap.y = p0->y;
	swap.z = p0->z;
	p0->x = p1->x;
	p0->y = p1->y;
	p0->z = p1->z;
	p1->x = swap.x;
	p1->y = swap.y;
	p1->z = swap.z;
}

static void	swap_uvz(t_uvz *p0, t_uvz *p1)
{
	t_uvz	swap;

	swap.u = p0->u;
	swap.v = p0->v;
	swap.w = p0->w;
	p0->u = p1->u;
	p0->v = p1->v;
	p0->w = p1->w;
	p1->u = swap.u;
	p1->v = swap.v;
	p1->w = swap.w;
}

static void	sort_vertices(t_triangle *tri)
{
	if (tri->p[0].y > tri->p[1].y)
	{
		swap_xyz(&tri->p[0], &tri->p[1]);
		swap_uvz(&tri->uv[0], &tri->uv[1]);
	}
	if (tri->p[0].y > tri->p[2].y)
	{
		swap_xyz(&tri->p[0], &tri->p[2]);
		swap_uvz(&tri->uv[0], &tri->uv[2]);
	}
	if (tri->p[1].y > tri->p[2].y)
	{
		swap_xyz(&tri->p[1], &tri->p[2]);
		swap_uvz(&tri->uv[1], &tri->uv[2]);
	}
}

static t_uvz	calculate_texel_delta_x(t_triangle *calculate, float denom)
{
	t_uvz texel_delta;

	texel_delta.w = (
		((calculate->uv[2].w - calculate->uv[0].w)
		* (calculate->p[1].y - calculate->p[0].y))
		- ((calculate->uv[1].w - calculate->uv[0].w)
		* (calculate->p[2].y - calculate->p[0].y))) * denom;
	texel_delta.u = (
		((calculate->uv[2].u - calculate->uv[0].u)
		* (calculate->p[1].y - calculate->p[0].y))
		- ((calculate->uv[1].u - calculate->uv[0].u)
		* (calculate->p[2].y - calculate->p[0].y))) * denom;
	texel_delta.v = (
		((calculate->uv[2].v - calculate->uv[0].v)
		* (calculate->p[1].y - calculate->p[0].y))
		- ((calculate->uv[1].v - calculate->uv[0].v)
		* (calculate->p[2].y - calculate->p[0].y))) * denom;
	return (texel_delta);
}

static t_uvz	calculate_texel_delta_y(t_triangle *calculate, float denom)
{
	t_uvz texel_delta;

	texel_delta.w = (
		((calculate->uv[1].w - calculate->uv[0].w)
		* (calculate->p[2].x - calculate->p[0].x))
		- ((calculate->uv[2].w - calculate->uv[0].w)
		* (calculate->p[1].x - calculate->p[0].x))) * denom;
	texel_delta.u = (
		((calculate->uv[1].u - calculate->uv[0].u)
		* (calculate->p[2].x - calculate->p[0].x))
		- ((calculate->uv[2].u - calculate->uv[0].u)
		* (calculate->p[1].x - calculate->p[0].x))) * denom;
	texel_delta.v = (
		((calculate->uv[1].v - calculate->uv[0].v)
		* (calculate->p[2].x - calculate->p[0].x))
		- ((calculate->uv[2].v - calculate->uv[0].v)
		* (calculate->p[1].x - calculate->p[0].x))) * denom;
	return (texel_delta);
}

static void fill_triangle(Uint32 *buffer, t_xy left, t_xy right,
	t_uvz texel_delta_x, t_uvz texel_delta_left, t_uvz uv,
	float pixel_delta_left, float pixel_delta_right, t_texture *tex)
{
	int		x1;
	int		x2;
	t_uvz	texel;
	t_uvz	corr_texel;
	Uint32	colour;
	int		left_y;
	int		right_y;

	left_y = left.y;
	right_y = right.y;
	while (left_y < right_y)
	{
		x1 = left.x;
		x2 = right.x;
		texel.w = uv.w + (1 - (left.x - x1)) * texel_delta_x.w;
		texel.u = uv.u + (1 - (left.x - x1)) * texel_delta_x.u;
		texel.v = uv.v + (1 - (left.x - x1)) * texel_delta_x.v;
		while (x1++ < x2)
		{
			corr_texel = texel_inv_z(texel);
			colour = get_texel(corr_texel.u * (tex->w - 1),
						corr_texel.v * (tex->h - 1), tex);
			put_pixel(buffer, x1, left_y, colour);
			texel.w += texel_delta_x.w;
			texel.u += texel_delta_x.u;
			texel.v += texel_delta_x.v;
		}
		left.x += pixel_delta_left;
		right.x += pixel_delta_right;
		uv.w += texel_delta_left.w;
		uv.u += texel_delta_left.u;
		uv.v += texel_delta_left.v;
		left_y++;
	}
}

void	calculate_triangle(t_frame *frame, t_triangle *tri, t_texture *tex)
{
	float	dxdy1;
	float	dxdy2;
	float	dxdy3;
	float	denom;
	float	dy;
	int		y1i;
	int		y2i;
	int		y3i;
	int		side;
	t_uvz	texel_delta_x;
	t_uvz	texel_delta_y;
	t_uvz	texel_delta_left;
	t_uvz	texel_left;
	float	pixel_delta_left;
	float	pixel_delta_right;
	float	x_left;
	float	x_right;
	t_triangle	calculate;

	calculate = *tri;
	calculate.p[0].x = tri->p[0].x + 0.5;
	calculate.p[0].y = tri->p[0].y + 0.5;
	calculate.p[1].x = tri->p[1].x + 0.5;
	calculate.p[1].y = tri->p[1].y + 0.5;
	calculate.p[2].x = tri->p[2].x + 0.5;
	calculate.p[2].y = tri->p[2].y + 0.5;
	calculate.uv[0] = texel_inv_z(tri->uv[0]);
	calculate.uv[1] = texel_inv_z(tri->uv[1]);
	calculate.uv[2] = texel_inv_z(tri->uv[2]);
	sort_vertices(&calculate);
	y1i = calculate.p[0].y;
	y2i = calculate.p[1].y;
	y3i = calculate.p[2].y;
	if ((y1i == y2i && y1i == y3i)
		|| ((int) calculate.p[0].x == (int) calculate.p[1].x
		&& (int) calculate.p[0].x == (int) calculate.p[2].x))
		return;
	denom = ((calculate.p[2].x - calculate.p[0].x) * (calculate.p[1].y - calculate.p[0].y)
			- (calculate.p[1].x - calculate.p[0].x) * (calculate.p[2].y - calculate.p[0].y));
	if (!denom)
		return;
	denom = 1 / denom;
	texel_delta_x = calculate_texel_delta_x(&calculate, denom);
	texel_delta_y = calculate_texel_delta_y(&calculate, denom);
	if (calculate.p[1].y > calculate.p[0].y)
		dxdy1 = interpolate_points(calculate.p[0].x, calculate.p[1].x, calculate.p[0].y, calculate.p[1].y);
	if (calculate.p[2].y > calculate.p[0].y)
		dxdy2 = interpolate_points(calculate.p[0].x, calculate.p[2].x, calculate.p[0].y, calculate.p[2].y);
	if (calculate.p[2].y > calculate.p[1].y)
		dxdy3 = interpolate_points(calculate.p[1].x, calculate.p[2].x, calculate.p[1].y, calculate.p[2].y);
	side = dxdy2 > dxdy1;
	if (calculate.p[0].y == calculate.p[1].y)
		side = calculate.p[0].x > calculate.p[1].x;
	if (calculate.p[1].y == calculate.p[2].y)
		side = calculate.p[2].x > calculate.p[1].x;
	if (!side)
	{
		pixel_delta_left = dxdy2;
		texel_delta_left = uvz_calculate_value_with_delta(pixel_delta_left, texel_delta_x, texel_delta_y);
		dy = 1 - (calculate.p[0].y - y1i);
		x_left = calculate.p[0].x + dy * pixel_delta_left;
		texel_left.w = calculate.uv[0].w + dy * texel_delta_left.w;
		texel_left.u = calculate.uv[0].u + dy * texel_delta_left.u;
		texel_left.v = calculate.uv[0].v + dy * texel_delta_left.v;
		if (y1i < y2i)
		{
			x_right = calculate.p[0].x + dy * dxdy1;
			pixel_delta_right = dxdy1;
			fill_triangle(frame->buffer,
				(t_xy){x_left, y1i}, (t_xy){x_right, y2i},
				texel_delta_x, texel_delta_left, texel_left,
				pixel_delta_left, pixel_delta_right, tex);
		}
		if (y2i < y3i)
		{
			x_right = calculate.p[1].x + (1 - (calculate.p[1].y - y2i)) * dxdy3;
			pixel_delta_right = dxdy3;
			fill_triangle(frame->buffer,
				(t_xy){x_left, y2i}, (t_xy){x_right, y3i},
				texel_delta_x, texel_delta_left, texel_left,
				pixel_delta_left, pixel_delta_right, tex);
		}
	}
	else
	{
		pixel_delta_right = dxdy2;
		dy = 1 - (calculate.p[0].y - y1i);
		x_right = calculate.p[0].x + dy * pixel_delta_right;
		if (y1i < y2i)
		{
			pixel_delta_left = dxdy1;
			texel_delta_left = uvz_calculate_value_with_delta(pixel_delta_left, texel_delta_x, texel_delta_y);
			x_left = calculate.p[0].x + dy * pixel_delta_left;
			texel_left.w = calculate.uv[0].w + dy * texel_delta_left.w;
			texel_left.u = calculate.uv[0].u + dy * texel_delta_left.u;
			texel_left.v = calculate.uv[0].v + dy * texel_delta_left.v;
			fill_triangle(frame->buffer,
				(t_xy){x_left, y1i}, (t_xy){x_right, y2i},
				texel_delta_x, texel_delta_left, texel_left,
				pixel_delta_left, pixel_delta_right, tex);
		}
		if (y2i < y3i)
		{
			pixel_delta_left = dxdy3;
			texel_delta_left = uvz_calculate_value_with_delta(pixel_delta_left, texel_delta_x, texel_delta_y);
			dy = 1 - (calculate.p[1].y - y2i);
			x_left = calculate.p[1].x + dy * pixel_delta_left;
			texel_left.w = calculate.uv[1].w + dy * texel_delta_left.w;
			texel_left.u = calculate.uv[1].u + dy * texel_delta_left.u;
			texel_left.v = calculate.uv[1].v + dy * texel_delta_left.v;
			fill_triangle(frame->buffer,
				(t_xy){x_left, y2i}, (t_xy){x_right, y3i},
				texel_delta_x, texel_delta_left, texel_left,
				pixel_delta_left, pixel_delta_right, tex);
		}
	}
}

int	painters_algorithm(const void *tri1, const void *tri2)
{
	if (triangle_calculate_average_z((t_triangle *)tri1)
		> triangle_calculate_average_z((t_triangle *)tri2))
		return (1);
	else
		return (0);
}

/*
**	1. Clipping doesn't work as it should, objects appear to be more perpendicular than they should.
**	2. Problem when I scaled, not with the matrices, when objects appeared longer.
*/
int	draw_cube(t_frame *frame, t_home *home, t_player *plr)
{
	int				i;
	int				j;
	int				nb_of_triangles_in_view;
	t_xyz			scale;
	t_xyz			normal;
	t_xyz			view_offset;
	t_m4x4			matrix;
	t_triangle		clipped_triangle[2];
	t_triangle		projected;
	int				nb_of_clipped_triangles;
	static float	degree = 0.0f;
	// t_xyz			light_direction;
	// static Uint32	cur_time;
	// t_texture		*tex;

	// (void)home;
	// tex = get_tex(-1, home->editor_tex);
	// if (frame->last_frame - cur_time > 66)
	// {
	// 	cur_time = frame->last_frame;
	// 	degree += 0.1f;
	// }
	// if (degree > TWO_PI)
	// 	degree = 0.0f;
	// light_direction = (t_xyz){0,0,-1};
	view_offset = (t_xyz){1.0f, 1.0f, 0.0f, 1.0f};
	i = 0;
	while (i < 12)
	{
		home->transformed_cube[i] = apply_world_matrix(0.1f, degree, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &home->cube[i]);
		i++;
	}
	plr->up = (t_xyz){0.0f,1.0f,0.0f,1.0f}; //Position player straight.
	plr->target = (t_xyz){0.0f, 0.0f, 1.0f, 0.0f}; //Position player's gaze forwards.
	matrix = rotation_matrix_y(plr->yaw);
	plr->look_dir = multi_vec_matrix(&plr->target, &matrix);
	plr->target = vec3_add(plr->camera, plr->look_dir);
	scale = (t_xyz){0.5 * SCREEN_WIDTH, 0.5 * SCREEN_HEIGHT, 1.0f, 1.0f};
	i = 0;
	j = 0;
	nb_of_triangles_in_view = 0;
	while (i < 12)
	{
		normal = triangle_normal(&home->transformed_cube[i]);
		if (vec3_dot_product(normal, vec3_dec(home->transformed_cube[i].p[0], plr->camera)) < 0)
		{
			home->view_cube = apply_camera(
				plr->camera, plr->target, plr->up, &home->transformed_cube[i]);
			nb_of_clipped_triangles = clip_against_plane(
				&home->viewport.near,
				&home->view_cube, &clipped_triangle[0], &clipped_triangle[1]);
			j = 0;
			while (j < nb_of_clipped_triangles)
			{
				projected = create_projection(&clipped_triangle[j]);
				projected.p[0] = vec3_div(projected.p[0], projected.p[0].w);
				projected.p[1] = vec3_div(projected.p[1], projected.p[1].w);
				projected.p[2] = vec3_div(projected.p[2], projected.p[2].w);
				projected.p[0].x *= -1.0f;
				projected.p[0].y *= -1.0f;
				projected.p[1].x *= -1.0f;
				projected.p[1].y *= -1.0f;
				projected.p[2].x *= -1.0f;
				projected.p[2].y *= -1.0f;
				projected.p[0] = vec3_add(projected.p[0], view_offset);
				projected.p[1] = vec3_add(projected.p[1], view_offset);
				projected.p[2] = vec3_add(projected.p[2], view_offset);
				// projected.p[0].x *= 0.5f * (float)SCREEN_WIDTH;
				// projected.p[0].y *= 0.5f * (float)SCREEN_HEIGHT;
				// projected.p[1].x *= 0.5f * (float)SCREEN_WIDTH;
				// projected.p[1].y *= 0.5f * (float)SCREEN_HEIGHT;
				// projected.p[2].x *= 0.5f * (float)SCREEN_WIDTH;
				// projected.p[2].y *= 0.5f * (float)SCREEN_HEIGHT;
				projected = scale_triangle(&projected, scale);
				home->triangles_in_view[nb_of_triangles_in_view] = projected;
				nb_of_triangles_in_view++;
				j++;
			}
		}
		i++;
	}
	//Check that algorithm works, z might be lost once we get here.
	qsort((void *)home->triangles_in_view, (size_t)nb_of_triangles_in_view,
		sizeof(t_triangle), painters_algorithm);
	j = 0;
	clip_to_viewport_edges(home->triangles_in_view, home->raster_queue,
	 	&home->viewport, nb_of_triangles_in_view, frame);
	// while (j < raster_triangles_count)
	// {
	// 	// calculate_triangle(frame, &home->triangles_in_view[r], tex);
	// 	// draw_polygon(frame, &home->triangles_in_view[j]);
	// }
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 10.0f}, "player_xyz", (t_plx_modifier){green, 2});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 38.0f}, ft_ftoa(plr->camera.x, 6), (t_plx_modifier){green, 2});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 24.0f}, ft_ftoa(plr->camera.y, 6), (t_plx_modifier){green, 2});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 38.0f}, ft_ftoa(plr->camera.z, 6), (t_plx_modifier){green, 2});
	return (TRUE);
}

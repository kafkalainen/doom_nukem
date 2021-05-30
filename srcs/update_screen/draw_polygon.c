/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_polygon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:35:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/28 16:00:55 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	painters_algorithm(const void *tri1, const void *tri2)
{
	if (triangle_calculate_average_z((t_triangle *)tri1)
		> triangle_calculate_average_z((t_triangle *)tri2))
		return (1);
	else
		return (0);
}

/*
*/
int	draw_cube(t_frame *frame, t_home *home, t_player *plr)
{
	int				i;
	int				j;
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
	t_texture		*tex;

	// (void)home;
	tex = get_tex(-1, home->editor_tex);
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
	home->triangles_in_view->size = 0;
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
				//Perspective correction
				projected.uv[0].u = projected.uv[0].u / projected.p[0].w;
				projected.uv[1].u = projected.uv[1].u / projected.p[1].w;
				projected.uv[2].u = projected.uv[2].u / projected.p[2].w;
				projected.uv[0].v = projected.uv[0].v / projected.p[0].w;
				projected.uv[1].v = projected.uv[1].v / projected.p[1].w;
				projected.uv[2].v = projected.uv[2].v / projected.p[2].w;
				projected.uv[0].w = 1.0f / projected.p[0].w;
				projected.uv[1].w = 1.0f / projected.p[1].w;
				projected.uv[2].w = 1.0f / projected.p[2].w;
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
				projected = scale_triangle(&projected, scale);
				home->triangles_in_view->array[home->triangles_in_view->size] = projected;
				home->triangles_in_view->size++;
				j++;
			}
		}
		i++;
	}
	//Check that algorithm works, z might be lost once we get here.
	qsort((void *)home->triangles_in_view->array, (size_t)home->triangles_in_view->size,
		sizeof(t_triangle), painters_algorithm);
	j = 0;
	clip_to_viewport_edges(home->triangles_in_view, home->raster_queue,
	 	&home->viewport, frame, tex);
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 10.0f}, "player_xyz", (t_plx_modifier){green, 2});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 38.0f}, ft_ftoa(plr->camera.x, 6), (t_plx_modifier){green, 2});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 24.0f}, ft_ftoa(plr->camera.y, 6), (t_plx_modifier){green, 2});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 38.0f}, ft_ftoa(plr->camera.z, 6), (t_plx_modifier){green, 2});
	return (TRUE);
}

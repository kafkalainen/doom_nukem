/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_polygon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:35:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/01 08:37:47 by jnivala          ###   ########.fr       */
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

static Uint32	transform_walls(t_sector *sector, t_raster_queue *transformed)
{
	Uint32	i;
	t_wall	*wall;

	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls * 2)
	{
		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &wall->top);
		i++;
		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &wall->bottom);
		i++;
		wall = wall->next;
	}
	transformed->size = i;
	return (TRUE);
}

static Uint32	clip_to_near_plane(t_triangle *current_view,
	t_sides *viewport, t_raster_queue *triangles_in_view)
{
	Uint32		nb_of_clipped_triangles;
	t_triangle	projected;
	t_xyz		scale;
	t_triangle	clipped_triangle[2];

	scale = (t_xyz){0.5 * SCREEN_WIDTH, 0.5 * SCREEN_HEIGHT, 1.0f, 1.0f};
	nb_of_clipped_triangles = clip_against_plane(&viewport->near,
		current_view, &clipped_triangle[0], &clipped_triangle[1]);
	while (nb_of_clipped_triangles)
	{
		projected = create_projection(&clipped_triangle[nb_of_clipped_triangles - 1]);
		triangle_inv_z(&projected);
		projected.p[0] = vec3_div(projected.p[0], projected.p[0].w);
		projected.p[1] = vec3_div(projected.p[1], projected.p[1].w);
		projected.p[2] = vec3_div(projected.p[2], projected.p[2].w);
		invert_view(&projected);
		triangle_add(&projected, viewport->view_offset);
		projected = scale_triangle(&projected, scale);
		triangles_in_view->array[triangles_in_view->size] = projected;
		triangles_in_view->size++;
		nb_of_clipped_triangles--;
	}
	return (TRUE);
}

static Uint32	project_to_player_position(t_raster_queue *transformed,
	t_raster_queue *triangles_in_view, t_player *plr, t_sides *view)
{
	Uint32		i;
	size_t		current_size;
	t_xyz		normal;
	t_triangle	current_viewed_triangle;

	create_target_vector(plr);
	current_size = transformed->size;
	triangles_in_view->size = 0;
	i = 0;
	while (i < current_size)
	{
		normal = triangle_normal(&transformed->array[i]);
		if (vec3_dot_product(normal, vec3_dec(transformed->array[i].p[0], plr->camera)) > 0)
		{
			current_viewed_triangle = apply_camera(
				plr->camera, plr->target, plr->up, &transformed->array[i]);
			clip_to_near_plane(&current_viewed_triangle, view, triangles_in_view);
		}
		i++;
	}
	return (TRUE);
}

int	draw_sector(t_frame *frame, t_home *home, t_sector *sector, t_player *plr)
{
	// static float	degree = 0.0f;
	t_texture		*tex;

	tex = get_tex(-1, home->editor_tex);
	// if (frame->last_frame - cur_time > 66)
	// {
	// 	cur_time = frame->last_frame;
	// 	degree += 0.1f;
	// }
	// if (degree > TWO_PI)
	// 	degree = 0.0f;
	transform_walls(sector, frame->transformed);
	project_to_player_position(frame->transformed, frame->triangles_in_view, plr, &frame->viewport);
	qsort((void *)frame->triangles_in_view->array,
		(size_t)frame->triangles_in_view->size, sizeof(t_triangle), painters_algorithm);
	clip_to_viewport_edges(frame->triangles_in_view, frame->raster_queue,
	 	&frame->viewport, frame, tex);
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 10.0f}, "player_xyz", (t_plx_modifier){green, 2});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 24.0f}, ft_ftoa(plr->camera.x, 6), (t_plx_modifier){green, 2});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 38.0f}, ft_ftoa(plr->camera.y, 6), (t_plx_modifier){green, 2});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 52.0f}, ft_ftoa(plr->camera.z, 6), (t_plx_modifier){green, 2});
	return (TRUE);
}


// int	draw_cube(t_frame *frame, t_home *home, t_player *plr)
// {
// 	int				i;
// 	int				j;
// 	t_xyz			scale;
// 	t_xyz			normal;
// 	t_xyz			view_offset;
// 	t_m4x4			matrix;
// 	t_triangle		clipped_triangle[2];
// 	t_triangle		projected;
// 	int				nb_of_clipped_triangles;
// 	static float	degree = 0.0f;
// 	// t_xyz			light_direction;
// 	// static Uint32	cur_time;
// 	t_texture		*tex;

// 	// (void)home;
// 	tex = get_tex(-1, home->editor_tex);
// 	// if (frame->last_frame - cur_time > 66)
// 	// {
// 	// 	cur_time = frame->last_frame;
// 	// 	degree += 0.1f;
// 	// }
// 	// if (degree > TWO_PI)
// 	// 	degree = 0.0f;
// 	// light_direction = (t_xyz){0,0,-1};
// 	view_offset = (t_xyz){1.0f, 1.0f, 0.0f, 1.0f};
// 	i = 0;
// 	while (i < 12)
// 	{
// 		home->transformed_cube[i] = apply_world_matrix(degree, degree, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &home->cube[i]);
// 		i++;
// 	}
// 	plr->up = (t_xyz){0.0f,1.0f,0.0f,1.0f}; //Position player straight.
// 	plr->target = (t_xyz){0.0f, 0.0f, 1.0f, 0.0f}; //Position player's gaze forwards.
// 	matrix = rotation_matrix_y(plr->yaw);
// 	plr->look_dir = multi_vec_matrix(&plr->target, &matrix);
// 	plr->target = vec3_add(plr->camera, plr->look_dir);
// 	scale = (t_xyz){0.5 * SCREEN_WIDTH, 0.5 * SCREEN_HEIGHT, 1.0f, 1.0f};
// 	i = 0;
// 	j = 0;
// 	home->triangles_in_view->size = 0;
// 	while (i < 12)
// 	{
// 		normal = triangle_normal(&home->transformed_cube[i]);
// 		if (vec3_dot_product(normal, vec3_dec(home->transformed_cube[i].p[0], plr->camera)) > 0)
// 		{
// 			home->view_cube = apply_camera(
// 				plr->camera, plr->target, plr->up, &home->transformed_cube[i]);
// 			nb_of_clipped_triangles = clip_against_plane(
// 				&home->viewport.near,
// 				&home->view_cube, &clipped_triangle[0], &clipped_triangle[1]);
// 			j = 0;
// 			while (j < nb_of_clipped_triangles)
// 			{
// 				projected = create_projection(&clipped_triangle[j]);
// 				//Perspective correction
// 				triangle_inv_z(&projected);
// 				projected.p[0] = vec3_div(projected.p[0], projected.p[0].w);
// 				projected.p[1] = vec3_div(projected.p[1], projected.p[1].w);
// 				projected.p[2] = vec3_div(projected.p[2], projected.p[2].w);
// 				projected.p[0].x *= -1.0f;
// 				projected.p[0].y *= -1.0f;
// 				projected.p[1].x *= -1.0f;
// 				projected.p[1].y *= -1.0f;
// 				projected.p[2].x *= -1.0f;
// 				projected.p[2].y *= -1.0f;
// 				projected.p[0] = vec3_add(projected.p[0], view_offset);
// 				projected.p[1] = vec3_add(projected.p[1], view_offset);
// 				projected.p[2] = vec3_add(projected.p[2], view_offset);
// 				projected = scale_triangle(&projected, scale);
// 				home->triangles_in_view->array[home->triangles_in_view->size] = projected;
// 				home->triangles_in_view->size++;
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// 	//Check that algorithm works, z might be lost once we get here.
// 	qsort((void *)home->triangles_in_view->array, (size_t)home->triangles_in_view->size,
// 		sizeof(t_triangle), painters_algorithm);
// 	j = 0;
// 	clip_to_viewport_edges(home->triangles_in_view, home->raster_queue,
// 	 	&home->viewport, frame, tex);
// 	ft_str_pxl(frame->buffer, (t_xy){5.0f, 10.0f}, "player_xyz", (t_plx_modifier){green, 2});
// 	ft_str_pxl(frame->buffer, (t_xy){5.0f, 38.0f}, ft_ftoa(plr->camera.x, 6), (t_plx_modifier){green, 2});
// 	ft_str_pxl(frame->buffer, (t_xy){5.0f, 24.0f}, ft_ftoa(plr->camera.y, 6), (t_plx_modifier){green, 2});
// 	ft_str_pxl(frame->buffer, (t_xy){5.0f, 38.0f}, ft_ftoa(plr->camera.z, 6), (t_plx_modifier){green, 2});
// 	return (TRUE);
// }

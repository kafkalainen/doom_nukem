/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_polygon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:35:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/23 15:05:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int		draw_polygon(t_frame *frame, t_triangle *tri)
{
	draw_line(vec2(tri->p[0].x, tri->p[0].y), vec2(tri->p[1].x, tri->p[1].y),
		white, frame->buffer);
	draw_line(vec2(tri->p[1].x, tri->p[1].y), vec2(tri->p[2].x, tri->p[2].y),
		white, frame->buffer);
	draw_line(vec2(tri->p[2].x, tri->p[2].y), vec2(tri->p[0].x, tri->p[0].y),
		white, frame->buffer);
	return (TRUE);
}

int		draw_cube(t_frame *frame)
{
	int			i;
	t_triangle	cube[12];
	t_triangle	project_cube[12];
	t_triangle	translated_cube[12];
	t_triangle	rot_cube[12];

	//SOUTH
	cube[0] = (t_triangle){(t_xyz){0,0,0}, (t_xyz){0,1,0}, (t_xyz){1,1,0}};
	cube[1] = (t_triangle){(t_xyz){0,0,0}, (t_xyz){1,1,0}, (t_xyz){1,0,0}};
	//EAST
	cube[2] = (t_triangle){(t_xyz){1,0,0}, (t_xyz){1,1,0}, (t_xyz){1,1,1}};
	cube[3] = (t_triangle){(t_xyz){1,0,0}, (t_xyz){1,1,1}, (t_xyz){1,0,1}};
	//NORTH
	cube[4] = (t_triangle){(t_xyz){1,0,1}, (t_xyz){1,1,1}, (t_xyz){0,1,1}};
	cube[5] = (t_triangle){(t_xyz){1,0,1}, (t_xyz){0,1,1}, (t_xyz){0,0,1}};
	//WEST
	cube[6] = (t_triangle){(t_xyz){0,0,1}, (t_xyz){0,1,1}, (t_xyz){0,1,0}};
	cube[7] = (t_triangle){(t_xyz){0,0,1}, (t_xyz){0,1,0}, (t_xyz){0,0,0}};
	//TOP
	cube[8] = (t_triangle){(t_xyz){0,1,0}, (t_xyz){0,1,1}, (t_xyz){1,1,1}};
	cube[9] = (t_triangle){(t_xyz){0,1,0}, (t_xyz){1,1,1}, (t_xyz){1,1,0}};
	//BOTTOM
	cube[10] = (t_triangle){(t_xyz){1,0,1}, (t_xyz){0,0,1}, (t_xyz){0,0,0}};
	cube[11] = (t_triangle){(t_xyz){1,0,1}, (t_xyz){0,0,0}, (t_xyz){1,0,0}};
	i = 0;
	while (i < 12)
	{
		rot_cube[i] = rotate_triangle(&cube[i], 40 * DEG_TO_RAD, 'z');
		rot_cube[i] = rotate_triangle(&rot_cube[i], 20 * DEG_TO_RAD, 'x');
		translated_cube[i] = rot_cube[i];
		translated_cube[i].p[0].z = cube[i].p[0].z + 3.0f;
		translated_cube[i].p[1].z = cube[i].p[1].z + 3.0f;
		translated_cube[i].p[2].z = cube[i].p[2].z + 3.0f;
		i++;
	}
	i = 0;
	while (i < 12)
	{
		project_cube[i] = create_projection(&translated_cube[i]);
		project_cube[i].p[0].x = project_cube[i].p[0].x + 1.0f;
		project_cube[i].p[0].y = project_cube[i].p[0].y + 1.0f;
		project_cube[i].p[1].x = project_cube[i].p[1].x + 1.0f;
		project_cube[i].p[1].y = project_cube[i].p[1].y + 1.0f;
		project_cube[i].p[2].x = project_cube[i].p[2].x + 1.0f;
		project_cube[i].p[2].y = project_cube[i].p[2].y + 1.0f;
		project_cube[i] = scale_triangle(&project_cube[i],
			(t_xyz){SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f});
		draw_polygon(frame, &project_cube[i]);
		i++;
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:16:15 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/03 12:06:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	init_south_west(t_triangle *face)
{
	face[0] = (t_triangle){{(t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){100.0f, 100.0f, 0.0f, 1.0f}, (t_xyz){0.0f, 100.0f, 0.0f, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f},
		(t_uvz){0.0f, 0.0f, 1.0f}}, (float){1.0f}, (float){1.0f},
		(float){1.0f}, white, -space, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[1] = (t_triangle){(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}, (t_xyz){100.0f,
		0.0f, 0.0f, 1.0f}, (t_xyz){100.0f, 100.0f, 0.0f, 1.0f}, {(t_uvz){0.0f,
		1.0f, 1.0f}, (t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[2] = (t_triangle){{(t_xyz){100.0f, 0.0f, 0.0f, 1.0f}, (t_xyz){100.0f,
		100.0f, 100.0f, 1.0f}, (t_xyz){100.0f, 100.0f, 0.0f, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}, (t_uvz){0.0f, 0.0f,
		1.0f}}, (float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[3] = (t_triangle){{(t_xyz){100.0f, 0.0f, 0.0f, 1.0f}, (t_xyz){100.0f,
		0.0f, 100.0f, 1.0f}, (t_xyz){100.0f, 100.0f, 100.0f, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f,
		1.0f}}, (float){1.0f}, (float){1.0f}, (float){1.0f},
		white, -space, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
}

static void	init_north_east(t_triangle *face)
{
	face[4] = (t_triangle){{(t_xyz){100.0f, 0.0f, 100.0f, 1.0f}, (t_xyz){0.0f,
		100.0f, 100.0f, 1.0f}, (t_xyz){100.0f, 100.0f, 100.0f, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f},
		(t_uvz){0.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[5] = (t_triangle){{(t_xyz){100.0f, 0.0f, 100.0f, 1.0f}, (t_xyz){0.0f,
		0.0f, 100.0f, 1.0f}, (t_xyz){0.0f, 100.0f, 100.0f, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f,
		0.0f, 1.0f}}, (float){1.0f}, (float){1.0f}, (float){1.0f},
		white, -space, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[6] = (t_triangle){{(t_xyz){0.0f, 0.0f, 100.0f, 1.0f}, (t_xyz){0.0f,
		100.0f, 0.0f, 1.0f}, (t_xyz){0.0f, 100.0f, 100.0f, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}, (t_uvz){0.0f,
		0.0f, 1.0f}}, (float){1.0f}, (float){1.0f}, (float){1.0f},
		white, -space, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[7] = (t_triangle){{(t_xyz){0.0f, 0.0f, 100.0f, 1.0f}, (t_xyz){0.0f,
		0.0f, 0.0f, 1.0f}, (t_xyz){0.0f, 100.0f, 0.0f, 1.0f}}, {(t_uvz){0.0f,
		1.0f, 1.0f}, (t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
}

static void	init_top_bottom(t_triangle *face)
{
	face[8] = (t_triangle){{(t_xyz){0.0f, 100.0f, 0.0f, 1.0f},
		(t_xyz){100.0f, 100.0f, 100.0f, 1.0f},
		(t_xyz){0.0f, 100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f, 1.0f, 0.0f},
		(t_uvz){1.0f, 0.0f, 1.0f}, (t_uvz){0.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[9] = (t_triangle){{(t_xyz){0.0f, 100.0f, 0.0f, 1.0f},
		(t_xyz){100.0f, 100.0f, 0.0f, 1.0f},
		(t_xyz){100.0f, 100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f, 1.0f, 1.0f},
		(t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[10] = (t_triangle){{(t_xyz){100.0f, 0.0f, 100.0f, 1.0f},
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){0.0f, 0.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f, 1.0f, 1.0f},
		(t_uvz){1.0f, 0.0f, 1.0f}, (t_uvz){0.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[11] = (t_triangle){{(t_xyz){100.0f, 0.0f, 100.0f, 1.0f},
		(t_xyz){100.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}}, {(t_uvz){0.0f, 1.0f, 1.0f},
		(t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
}

static void	translate_skybox(t_triangle *face)
{
	Uint32	i;

	i = 0;
	while (i < 12)
	{
		face[i] = apply_world_matrix(0.0f, 0.0f,
				(t_xyz){-50.0f, -50.0f, -50.0f, 0.0f}, &face[i]);
		i++;
	}
}

int	initialize_skybox(t_skybox *skybox)
{
	Uint32	i;

	i = 0;
	skybox->face = (t_triangle *)malloc(sizeof(t_triangle) * 12);
	if (skybox->face == NULL)
		return (1);
	init_south_west(skybox->face);
	init_north_east(skybox->face);
	init_top_bottom(skybox->face);
	while (i < 12)
	{
		skybox->face[i].normal = triangle_normal(&skybox->face[i]);
		i++;
	}
	translate_skybox(skybox->face);
	skybox->idx = -1;
	return (0);
}

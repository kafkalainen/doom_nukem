/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:16:15 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/21 10:51:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	init_south_west(t_triangle *face, float max)
{
	face[0] = (t_triangle){{(t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){max, max, 0.0f, 1.0f}, (t_xyz){0.0f, max, 0.0f, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f},
		(t_uvz){0.0f, 0.0f, 1.0f}}, (float){1.0f}, (float){1.0f},
		(float){1.0f}, white, -space, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[1] = (t_triangle){(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}, (t_xyz){max,
		0.0f, 0.0f, 1.0f}, (t_xyz){max, max, 0.0f, 1.0f}, {(t_uvz){0.0f,
		1.0f, 1.0f}, (t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[2] = (t_triangle){{(t_xyz){max, 0.0f, 0.0f, 1.0f}, (t_xyz){max,
		max, max, 1.0f}, (t_xyz){max, max, 0.0f, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}, (t_uvz){0.0f, 0.0f,
		1.0f}}, (float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[3] = (t_triangle){{(t_xyz){max, 0.0f, 0.0f, 1.0f}, (t_xyz){max,
		0.0f, max, 1.0f}, (t_xyz){max, max, max, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f,
		1.0f}}, (float){1.0f}, (float){1.0f}, (float){1.0f},
		white, -space, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
}

static void	init_north_east(t_triangle *face, float max)
{
	face[4] = (t_triangle){{(t_xyz){max, 0.0f, max, 1.0f}, (t_xyz){0.0f,
		max, max, 1.0f}, (t_xyz){max, max, max, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f},
		(t_uvz){0.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[5] = (t_triangle){{(t_xyz){max, 0.0f, max, 1.0f}, (t_xyz){0.0f,
		0.0f, max, 1.0f}, (t_xyz){0.0f, max, max, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f,
		0.0f, 1.0f}}, (float){1.0f}, (float){1.0f}, (float){1.0f},
		white, -space, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[6] = (t_triangle){{(t_xyz){0.0f, 0.0f, max, 1.0f}, (t_xyz){0.0f,
		max, 0.0f, 1.0f}, (t_xyz){0.0f, max, max, 1.0f}},
	{(t_uvz){0.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}, (t_uvz){0.0f,
		0.0f, 1.0f}}, (float){1.0f}, (float){1.0f}, (float){1.0f},
		white, -space, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[7] = (t_triangle){{(t_xyz){0.0f, 0.0f, max, 1.0f}, (t_xyz){0.0f,
		0.0f, 0.0f, 1.0f}, (t_xyz){0.0f, max, 0.0f, 1.0f}}, {(t_uvz){0.0f,
		1.0f, 1.0f}, (t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
}

static void	init_top_bottom(t_triangle *face, float max)
{
	face[8] = (t_triangle){{(t_xyz){0.0f, max, 0.0f, 1.0f},
		(t_xyz){max, max, max, 1.0f},
		(t_xyz){0.0f, max, max, 1.0f}}, {(t_uvz){0.0f, 1.0f, 0.0f},
		(t_uvz){1.0f, 0.0f, 1.0f}, (t_uvz){0.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[9] = (t_triangle){{(t_xyz){0.0f, max, 0.0f, 1.0f},
		(t_xyz){max, max, 0.0f, 1.0f},
		(t_xyz){max, max, max, 1.0f}}, {(t_uvz){0.0f, 1.0f, 1.0f},
		(t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[10] = (t_triangle){{(t_xyz){max, 0.0f, max, 1.0f},
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){0.0f, 0.0f, max, 1.0f}}, {(t_uvz){0.0f, 1.0f, 1.0f},
		(t_uvz){1.0f, 0.0f, 1.0f}, (t_uvz){0.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
	face[11] = (t_triangle){{(t_xyz){max, 0.0f, max, 1.0f},
		(t_xyz){max, 0.0f, 0.0f, 1.0f},
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}}, {(t_uvz){0.0f, 1.0f, 1.0f},
		(t_uvz){1.0f, 1.0f, 1.0f}, (t_uvz){1.0f, 0.0f, 1.0f}},
		(float){1.0f}, (float){1.0f}, (float){1.0f}, white, -space,
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}};
}

static void	translate_skybox(t_triangle *face, float max)
{
	Uint32	i;

	i = 0;
	while (i < 12)
	{
		face[i] = apply_world_matrix(0.0f, 0.0f,
				(t_xyz){-max * 0.5f, -max * 0.5f,
					-max * 0.5f, 0.0f}, &face[i]);
		i++;
	}
}

int	initialize_skybox(t_skybox *skybox, t_sector **sectors, t_uint nb_of_sectors)
{
	Uint32	i;
	float	max;

	i = 0;
	skybox->face = (t_triangle *)malloc(sizeof(t_triangle) * 12);
	if (skybox->face == NULL)
		return (1);
	get_map_maximum_values(&max, sectors, nb_of_sectors);
	max *= 2.0f;
	max += 100.0f;
	init_south_west(skybox->face, max);
	init_north_east(skybox->face, max);
	init_top_bottom(skybox->face, max);
	while (i < 12)
	{
		skybox->face[i].normal = triangle_normal(&skybox->face[i]);
		i++;
	}
	translate_skybox(skybox->face, max);
	skybox->idx = -1;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:21:40 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/07 17:21:40 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void init_viewmodel_layer(t_triangle *face)
{
	face[0] = (t_triangle){
		{(t_xyz){0.0f,100.0f, 0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 100.0f, 1.0f},
		(t_xyz){0.0f,100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,0.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}},
		{(t_xyz){0.0f,0.0f,0.0f,1.0f}, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){0.0f,0.0f,0.0f,1.0f}}, (float){1.0f}, (float){1.0f},
		(float){1.0f}, white, SKYBOX_TEX, (t_xyz){0.0f,0.0f,0.0f,1.0f}};
	face[1] = (t_triangle){
		{(t_xyz){0.0f,100.0f, 0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 0.0f,1.0f},
		(t_xyz){100.0f, 100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,1.0f,1.0f}, (t_uvz){1.0f,0.0f,1.0f}},
		{(t_xyz){0.0f,0.0f,0.0f,1.0f}, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){0.0f,0.0f,0.0f,1.0f}}, (float){1.0f}, (float){1.0f},
		(float){1.0f}, white, SKYBOX_TEX, (t_xyz){0.0f,0.0f,0.0f,1.0f}};
}

static void	init_hud_normals(t_triangle *face)
{
	Uint32	i;

	i = 0;
	while (i < 12)
	{
		face[i].normal = triangle_normal(&face[i]);
		i++;
	}
}

int		initialize_hud(t_hud *hud)
{
	skybox->face = (t_triangle*)malloc(sizeof(t_triangle) * 4);
	if (skybox->face == NULL)
		return (1);
	init_viewmodel_layer();
	init_hud_normals(skybox->face);
	skybox->idx = -1;
	return (0);
}

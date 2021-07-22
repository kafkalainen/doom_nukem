/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:21:40 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/21 14:02:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void init_viewmodel_layer(t_triangle *face)
{
	face[0] = (t_triangle){
		{(t_xyz){0.0f, SCREEN_HEIGHT, 0.0f, 1.0f}, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){SCREEN_WIDTH, 0.0f, 0.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,0.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}},
		{(t_xyz){0.0f,0.0f,0.0f,1.0f}, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){0.0f,0.0f,0.0f,1.0f}}, (float){1.0f}, (float){1.0f},
		(float){1.0f}, white, SKYBOX_TEX, (t_xyz){0.0f,0.0f,0.0f,1.0f}};

	face[1] = (t_triangle){
		{(t_xyz){0.0f, SCREEN_HEIGHT, 0.0f, 1.0f}, (t_xyz){SCREEN_WIDTH, 0.0f, 0.0f, 1.0f},
		(t_xyz){SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,0.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}},
		{(t_xyz){0.0f,0.0f,0.0f,1.0f}, (t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){0.0f,0.0f,0.0f,1.0f}}, (float){1.0f}, (float){1.0f},
		(float){1.0f}, white, SKYBOX_TEX, (t_xyz){0.0f,0.0f,0.0f,1.0f}};
}

static void	init_hud_normals(t_triangle *face)
{
	Uint32	i;

	i = 0;
	while (i < 2)
	{
		face[i].normal = triangle_normal(&face[i]);
		i++;
	}
}

int		initialize_hud(t_hud *hud)
{
	hud->viewmodel = (t_triangle*)malloc(sizeof(t_triangle) * 2);
	if (hud->viewmodel == NULL)
		return (1);
	init_viewmodel_layer(hud->viewmodel);
	init_hud_normals(hud->viewmodel);
	hud->idx[0] = -1;
	hud->idx[1] = -1;
	return (0);
}

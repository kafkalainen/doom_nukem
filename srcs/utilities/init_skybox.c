/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:16:15 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/24 11:49:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	init_south_west(t_triangle *face)
{
	face[0] = (t_triangle){
		{(t_xyz){0.0f,0.0f,0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 0.0f, 1.0f},
		(t_xyz){0.0f,100.0f,0.0f,1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}}, white, SKYBOX_TEX
		, 1.0f};
	face[1] = (t_triangle){
		(t_xyz){0.0f, 0.0f, 0.0f, 1.0f}, (t_xyz){100.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){100.0f, 100.0f, 0.0f,1.0f}, {(t_uvz){0.0f, 1.0f, 1.0f},
		(t_uvz){1.0f,1.0f,1.0f}, (t_uvz){1.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
	face[2] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 100.0f, 1.0f},
		(t_xyz){100.0f, 100.0f, 0.0f,1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
	face[3] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,0.0f,1.0f}, (t_xyz){100.0f, 0.0f,100.0f, 1.0f},
		(t_xyz){100.0f, 100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,1.0f,1.0f}, (t_uvz){1.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
}

static void init_north_east(t_triangle *face)
{

	face[4] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,100.0f, 1.0f}, (t_xyz){0.0f,100.0f, 100.0f, 1.0f},
		(t_xyz){100.0f, 100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
	face[5] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,100.0f, 1.0f}, (t_xyz){0.0f,0.0f,100.0f, 1.0f},
		(t_xyz){0.0f,100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,1.0f,1.0f}, (t_uvz){1.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
	face[6] = (t_triangle){
		{(t_xyz){0.0f,0.0f,100.0f, 1.0f}, (t_xyz){0.0f,100.0f, 0.0f,1.0f},
		(t_xyz){0.0f,100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
	face[7] = (t_triangle){
		{(t_xyz){0.0f,0.0f,100.0f, 1.0f}, (t_xyz){0.0f,0.0f,0.0f,1.0f},
		(t_xyz){0.0f,100.0f, 0.0f,1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,1.0f,1.0f}, (t_uvz){1.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
}

static void init_top_bottom(t_triangle *face)
{
	face[8] = (t_triangle){
		{(t_xyz){0.0f,100.0f, 0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 100.0f, 1.0f},
		(t_xyz){0.0f,100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,0.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
	face[9] = (t_triangle){
		{(t_xyz){0.0f,100.0f, 0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 0.0f,1.0f},
		(t_xyz){100.0f, 100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,1.0f,1.0f}, (t_uvz){1.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
	face[10] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,100.0f, 1.0f}, (t_xyz){0.0f,0.0f,0.0f,1.0f},
		(t_xyz){0.0f,0.0f,100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
	face[11] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,100.0f, 1.0f}, (t_xyz){100.0f, 0.0f,0.0f,1.0f},
		(t_xyz){0.0f,0.0f,0.0f,1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,1.0f,1.0f}, (t_uvz){1.0f,0.0f,1.0f}}, white, SKYBOX_TEX,
		1.0f};
}

int		initialize_skybox(t_skybox *skybox)
{
	skybox->face = (t_triangle*)malloc(sizeof(t_triangle) * 12);
	if (skybox->face == NULL)
		return (1);
	init_south_west(skybox->face);
	init_north_east(skybox->face);
	init_top_bottom(skybox->face);
	skybox->idx = -1;
	return (0);
}

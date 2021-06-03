/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:16:15 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/02 17:39:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	init_south_west_east(t_triangle *face)
{
	face[0] = (t_triangle){
		{(t_xyz){0.0f,0.0f,0.0f,1.0f}, (t_xyz){0.0f,100.0f,0.0f,1.0f},
		(t_xyz){100.0f, 100.0f, 0.0f,1.0f}}, {(t_uvz){0.0f,1.0f,0.0f},
		(t_uvz){0.0f,0.0f,0.0f}, (t_uvz){1.0f,0.0f,0.0f}}, white};
	face[1] = (t_triangle){
		(t_xyz){0.0f,0.0f,0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 0.0f,1.0f},
		(t_xyz){100.0f, 0.0f,0.0f,1.0f}, {(t_uvz){0.0f,1.0f,0.0f},
		(t_uvz){1.0f,0.0f,0.0f}, (t_uvz){1.0f,1.0f,0.0f}}, white};
	face[2] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 0.0f,1.0f},
		(t_xyz){100.0f, 100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,0.0f},
		(t_uvz){0.0f,0.0f,0.0f}, (t_uvz){1.0f,0.0f,1.0f}}, white};
	face[3] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 100.0f, 1.0f},
		(t_xyz){100.0f, 0.0f,100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,0.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){1.0f,1.0f,1.0f}}, white};
	face[4] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,100.0f, 1.0f}, (t_xyz){100.0f, 100.0f, 100.0f, 1.0f},
		(t_xyz){0.0f,100.0f, 100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){0.0f,0.0f,1.0f}, (t_uvz){1.0f,0.0f,1.0f}}, white};
	face[5] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,100.0f, 1.0f}, (t_xyz){0.0f,100.0f, 100.0f, 1.0f},
		(t_xyz){0.0f,0.0f,100.0f, 1.0f}}, {(t_uvz){0.0f,1.0f,1.0f},
		(t_uvz){1.0f,0.0f,1.0f}, (t_uvz){1.0f,1.0f,1.0f}}, white};
}

static void init_north_top_bottom(t_triangle *face)
{
	face[6] = (t_triangle){
		{(t_xyz){0.0f,0.0f,100.0f, 1.0f}, (t_xyz){0.0f,100.0f, 100.0f, 1.0f}, (t_xyz){0.0f,100.0f, 0.0f,1.0f}},
		{(t_uvz){0.0f,1.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}, (t_uvz){1.0f,0.0f,0.0f}}, white};
	face[7] = (t_triangle){
		{(t_xyz){0.0f,0.0f,100.0f, 1.0f}, (t_xyz){0.0f,100.0f, 0.0f,1.0f}, (t_xyz){0.0f,0.0f,0.0f,1.0f}},
		{(t_uvz){0.0f,1.0f,1.0f}, (t_uvz){1.0f,0.0f,0.0f}, (t_uvz){1.0f,1.0f,0.0f}}, white};
	face[8] = (t_triangle){
		{(t_xyz){0.0f,100.0f, 0.0f,1.0f}, (t_xyz){0.0f,100.0f, 100.0f, 1.0f}, (t_xyz){100.0f, 100.0f, 100.0f, 1.0f}},
		{(t_uvz){0.0f,1.0f,0.0f}, (t_uvz){0.0f,0.0f,1.0f}, (t_uvz){1.0f,0.0f,1.0f}}, white};
	face[9] = (t_triangle){
		{(t_xyz){0.0f,100.0f, 0.0f,1.0f}, (t_xyz){100.0f, 100.0f, 100.0f, 1.0f}, (t_xyz){100.0f, 100.0f, 0.0f,1.0f}},
		{(t_uvz){0.0f,1.0f,0.0f}, (t_uvz){1.0f,0.0f,1.0f}, (t_uvz){1.0f,1.0f,1.0f}}, white};
	face[10] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,100.0f, 1.0f}, (t_xyz){0.0f,0.0f,100.0f, 1.0f}, (t_xyz){0.0f,0.0f,0.0f,1.0f}},
		{(t_uvz){0.0f,1.0f,1.0f}, (t_uvz){0.0f,0.0f,1.0f}, (t_uvz){1.0f,0.0f,0.0f}}, white};
	face[11] = (t_triangle){
		{(t_xyz){100.0f, 0.0f,100.0f, 1.0f}, (t_xyz){0.0f,0.0f,0.0f,1.0f}, (t_xyz){100.0f, 0.0f,0.0f,1.0f}},
		{(t_uvz){0.0f,1.0f,1.0f}, (t_uvz){1.0f,0.0f,0.0f}, (t_uvz){1.0f,1.0f,0.0f}}, white};
}

int		init_skybox(t_skybox *skybox)
{
	skybox->face = (t_triangle*)malloc(sizeof(t_triangle) * 12);
	if (skybox->face == NULL)
		return (1);
	init_south_west_east(skybox->face);
	init_north_top_bottom(skybox->face);
	skybox->idx = -1;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/09 10:57:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_texel	*get_tex(int idx, t_texture	**textures)
{
	int	i;

	if (idx >= 0)
		error_output("idx larger or equal to zero\n");
	i = 1;
	while (textures[i])
	{
		if (textures[i]->idx == idx)
			return (&textures[i]->tex);
		i++;
	}
	return (NULL);
}

// static Uint32	transform_walls(t_home *home, t_sector *sector, t_raster_queue *transformed)
// {
// 	Uint32		i;
// 	Uint32		j;
// 	Uint32		k;
// 	Uint32		l;
// 	t_wall		*wall;
// 	t_surface	*ground;
// 	t_surface	*ceiling;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	l = 0;
// 	wall = sector->walls;
// 	ground = sector->ground;
// 	ceiling = sector->ceiling;
// 	while (i < 12)
// 	{
// 		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){-50.0f, -50.0f, -50.0f, 0.0f}, &home->skybox.face[i]);
// 		i++;
// 	}
// 	while (j < sector->nb_of_walls * 2)
// 	{
// 		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &wall->top);
// 		i++;
// 		j++;
// 		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &wall->bottom);
// 		i++;
// 		j++;
// 		wall = wall->next;
// 	}
// 	while (k < 4)
// 	{
// 		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &ground->tri);
// 		i++;
// 		k++;
// 		ground = ground->next;
// 	}
// 	while (l < 4)
// 	{
// 		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &ceiling->tri);
// 		i++;
// 		l++;
// 		ceiling = ceiling->next;
// 	}
// 	transformed->size = i;
// 	return (TRUE);
// }

void	scan_fov(t_home *home, t_frame *frame, t_player *plr)
{
	t_frame			new_frame;
	t_triangle		temp_array[100];
	t_surface		*ground;
	t_surface		*ceiling;
	unsigned int	j;

	ground = home->sectors[frame->idx]->ground;
	ceiling = home->sectors[frame->idx]->ceiling;
	frame->left.wall = home->sectors[frame->idx]->walls;
	frame->transformed->size = 0;
	continue_from_last_sector(frame->left.wall, &frame->left, frame);
	// get_wall_pts(frame, home->sectors[frame->idx]->nb_of_walls, plr);
	j = 0;
	while (frame->transformed->size < (int)home->sectors[frame->idx]->nb_of_walls * 2)
	{
		if (frame->left.wall->top.idx >= 0)
		{
			if (!check_connection(frame->left.wall, frame))
			{
				setup_frame(frame, &new_frame, frame->left.wall->top.idx);
				scan_fov(home, &new_frame, plr);
			}
		}
		else
		{
			temp_array[frame->transformed->size++] = frame->left.wall->top;
			temp_array[frame->transformed->size++] = frame->left.wall->bottom;
		}
		frame->left.wall = frame->left.wall->next;
	}
	j = 0;
	while (j < home->sectors[frame->idx]->nb_of_ceil)
	{
		temp_array[frame->transformed->size++] = ceiling->tri;
		ceiling = ceiling->next;
		j++;
	}
	j = 0;
	while (j < home->sectors[frame->idx]->nb_of_ground)
	{
		temp_array[frame->transformed->size++] = ground->tri;
		ground = ground->next;
		j++;
	}
	// j = 0;
	// while (j < 12)
	// {
	// 	temp_array[frame->transformed->size++] = apply_world_matrix(0.0f, 0.0f, (t_xyz){-50.0f, -50.0f, -50.0f, 0.0f}, &home->skybox.face[j]);
	// 	j++;
	// }
	j = 0;
	while ((int)j < frame->transformed->size)
	{
		frame->transformed->array[j] = temp_array[j];
		j++;
	}
	draw_sector(frame, home, plr);
}

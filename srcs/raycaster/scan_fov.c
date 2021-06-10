/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/09 15:02:55 by jnivala          ###   ########.fr       */
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

void	scan_fov(t_home *home, t_frame *frame, t_player *plr)
{
	t_frame			new_frame;
	t_triangle		temp_array[200];
	t_surface		*ground;
	t_surface		*ceiling;
	unsigned int	j;

	ground = home->sectors[frame->idx]->ground;
	ceiling = home->sectors[frame->idx]->ceiling;
	frame->left.wall = home->sectors[frame->idx]->walls;
	frame->transformed->size = 0;
	continue_from_last_sector(frame->left.wall, &frame->left, frame);
	j = 0;
	while (j < home->sectors[frame->idx]->nb_of_walls * 2)
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
			temp_array[j++] = frame->left.wall->top;
			temp_array[j++] = frame->left.wall->bottom;
		}
		frame->left.wall = frame->left.wall->next;
	}
	frame->transformed->size = j;
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

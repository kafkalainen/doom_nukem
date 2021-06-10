/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/10 16:24:58 by jnivala          ###   ########.fr       */
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

void	add_floor_and_ceiling(t_raster_queue *transformed, t_sector *sector)
{
	Uint32			j;
	t_surface		*ground;
	t_surface		*ceiling;

	ground = sector->ground;
	ceiling = sector->ceiling;
	j = 0;

	while (j < sector->nb_of_ceil)
	{
		transformed->array[transformed->size] = ceiling->tri;
		transformed->size += 1;
		ceiling = ceiling->next;
		j++;
	}
	j = 0;
	while (j < sector->nb_of_ground)
	{
		transformed->array[transformed->size] = ground->tri;
		transformed->size += 1;
		ground = ground->next;
		j++;
	}
}

void	scan_fov(t_home *home, t_frame *frame, t_player *plr)
{
	t_frame			new_frame;
	t_triangle		temp_array[200];
	unsigned int	j;

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
	while ((int)j < frame->transformed->size)
	{
		frame->transformed->array[j] = temp_array[j];
		j++;
	}
	add_floor_and_ceiling(frame->transformed, home->sectors[frame->idx]);
	draw_sector(frame, home, plr);
}

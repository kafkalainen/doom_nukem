/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/02 16:27:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_texel	*get_tex(int idx, t_texture	**textures)
{
	if (idx >= 0)
		error_output("idx larger or equal to zero\n");
	idx = -idx;
	return (&textures[idx]->tex);
}

void	fill_rasterqueue(t_home *home, t_frame *frame, t_player *plr)
{
	add_walls(home, frame, plr);
	add_ground(home, frame, plr);
	add_ceiling(home, frame, plr);
	add_objects(home, frame, plr);
}

void	scan_fov(t_home *home, t_frame *frame, t_player *plr)
{
	unsigned int	j;
	t_frame			new_frame;

	j = 0;
	quick_reset_queue(frame->transformed);
	frame->left.wall = home->sectors[frame->idx]->walls;
	continue_from_last_sector(frame->left.wall, &frame->left, frame);
	while (j < home->sectors[frame->idx]->nb_of_walls
		&& !check_connection(frame->left.wall, frame))
	{
		if (check_if_open_portal(frame->left.wall))
		{
			if (vec3_dot_product(frame->left.wall->top.normal,
					plr->look_dir) < SQR2)
			{
				setup_frame(frame, &new_frame, frame->left.wall->top.idx);
				scan_fov(home, &new_frame, plr);
			}
		}
		frame->left.wall = frame->left.wall->next;
		j++;
	}
	fill_rasterqueue(home, frame, plr);
	if (frame->transformed->size > 0)
		draw_sector(frame, home, plr, frame->idx);
}

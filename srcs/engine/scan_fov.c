/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/01 11:14:48 by jnivala          ###   ########.fr       */
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
	add_projectiles(home, frame, plr);
}

static t_wall	*cast_ray(t_wall *wall, unsigned int nb_of_walls,
				t_xy pos, t_ray_pt *ray)
{
	float	t;
	t_wall	*temp;

	temp = wall;
	while (nb_of_walls--)
	{
		if (vec2_get_scalar_to_intersection(pos, ray->dir, temp, &t))
		{
			ray->isection = vec2_add(pos, vec2_mul(ray->dir, t));
			return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}

/*
**	In setup_frame define leftmost and rightmost vector
**	using plr_pos and wallpoints. In first loop, you
**	will need to use 1.0f and -1.0f rad at rotation matrix.
**	and afterwards vec2_unit_vector(plr_pos, triangle->p[0], and triangle->p[2]);
**	Create boolean function, which will seek intersection between 2d wall and player
**	direction.
*/
static void	cast_rays_player_view(t_home *home, t_frame *frame, t_player *plr)
{
	t_frame	new_frame;
	t_xy 	plr_2d_pos;

	plr_2d_pos = vec3_to_vec2(plr->pos);
	frame->left.wall = cast_ray(home->sectors[frame->idx]->walls,
		home->sectors[frame->idx]->nb_of_walls, plr_2d_pos, &frame->left);
	frame->right.wall = cast_ray(home->sectors[frame->idx]->walls,
		home->sectors[frame->idx]->nb_of_walls, plr_2d_pos, &frame->right);
	if (!frame->right.wall || !frame->left.wall)
		return ;
	while (frame->left.wall != frame->right.wall
		&& !check_connection(frame->left.wall, frame))
	{
		if (check_if_portal(frame->left.wall))
		{
			frame->left.isection = vec2(frame->left.wall->top.p[1].x,
				frame->left.wall->top.p[1].z);
			setup_frame(frame, &new_frame, plr_2d_pos, frame->left.wall->top.idx);
			scan_fov(home, &new_frame, plr);
		}
		frame->left.wall = frame->left.wall->next;
	}
	if (check_if_portal(frame->right.wall)
		&& !check_connection(frame->right.wall, frame))
	{
		frame->left.isection = vec2(frame->left.wall->top.p[1].x,
				frame->left.wall->top.p[1].z);
		setup_frame(frame, &new_frame, plr_2d_pos, frame->left.wall->top.idx);
		scan_fov(home, &new_frame, plr);
	}
}

void	scan_fov(t_home *home, t_frame *frame, t_player *plr)
{
	quick_reset_queue(frame->transformed);
	cast_rays_player_view(home, frame, plr);
	fill_rasterqueue(home, frame, plr);
	if (frame->transformed->size > 0)
		draw_sector(frame, home, plr, frame->idx);
}

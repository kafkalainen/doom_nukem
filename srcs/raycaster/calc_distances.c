/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distances.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:27:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/15 13:37:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	calc_distances(t_frame *frame, t_texture *tex, t_player *plr)
{
	float	left_z;
	float	right_z;
	
	left_z = vec2_perp_dist(frame->left.l_pt);
	right_z = vec2_perp_dist(frame->left.r_pt);
	frame->top_left.x = SCREEN_WIDTH - ((SCREEN_HEIGHT /
		left_z) * frame->left.l_pt.x) + 15;
	frame->top_right.x = SCREEN_WIDTH - ((SCREEN_HEIGHT /
		right_z) * frame->left.r_pt.x) + 15;
	frame->top_left.z = left_z;
	frame->top_right.z = right_z;
	frame->bottom_left = frame->top_left;
	frame->bottom_right = frame->top_right;
	frame->top_left.y = plr->pitch - SCREEN_HEIGHT / left_z * 20;
	frame->top_right.y = plr->pitch - SCREEN_HEIGHT / right_z * 20;
	frame->bottom_left.y = plr->pitch + SCREEN_HEIGHT / left_z * 20;
	frame->bottom_right.y = plr->pitch + SCREEN_HEIGHT / right_z * 20;
	frame->visible_wall_dist = get_distance(frame->left.l_pt, frame->left.r_pt);
	frame->full_wall_dist = get_distance(frame->left.wall->x0, frame->left.wall->next->x0);
	frame->screen_wall_len = frame->top_right.x - frame->top_left.x;
	frame->full_wall_len = (frame->screen_wall_len * frame->full_wall_dist) / frame->visible_wall_dist;
	frame->ratio = frame->visible_wall_dist / frame->full_wall_dist;
	frame->tex_mult = frame->full_wall_dist / tex->w;
	// if (frame->left.wall == frame->right.wall)
	// {
		frame->unvisible_l_side = get_distance(frame->left.wall->x0, frame->left.l_pt) / frame->full_wall_dist;
		frame->unvisible_r_side = get_distance(frame->left.wall->next->x0, frame->left.r_pt) / frame->full_wall_dist;
		// frame->wall_fract_len = frame->full_wall_len 
		// 	* get_distance(frame->left.wall->x0, frame->left.l_pt)
		// 	/ frame->full_wall_dist;
	// }
}

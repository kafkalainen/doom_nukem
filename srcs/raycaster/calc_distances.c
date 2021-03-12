/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distances.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:27:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/11 13:57:54 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	calc_distances(t_frame *frame, t_texture *tex, t_player *plr)
{
	frame->top_left.z = vec2_perp_dist(frame->left.l_pt);
	frame->top_right.z = vec2_perp_dist(frame->left.r_pt);
	frame->top_left.x = SCREEN_WIDTH - ((SCREEN_HEIGHT /
		frame->top_left.z) * frame->left.l_pt.x) + 15;
	frame->top_right.x = SCREEN_WIDTH - ((SCREEN_HEIGHT /
		frame->top_right.z) * frame->left.r_pt.x) + 15;
	frame->bottom_left = frame->top_left;
	frame->bottom_right = frame->top_right;
	frame->top_left.y = plr->pitch - SCREEN_HEIGHT / frame->top_left.z * 20;
	frame->top_right.y = plr->pitch - SCREEN_HEIGHT / frame->top_right.z * 20;
	frame->bottom_left.y = plr->pitch + SCREEN_HEIGHT / frame->bottom_left.z * 20;
	frame->bottom_right.y = plr->pitch + SCREEN_HEIGHT / frame->bottom_right.z * 20;
	frame->visible_wall_dist = get_distance(frame->left.l_pt, frame->left.r_pt);
	frame->full_wall_dist = get_distance(frame->left.wall->x0, frame->left.wall->next->x0);
	frame->screen_wall_len = frame->top_right.x - frame->top_left.x;
	frame->full_wall_len = (frame->screen_wall_len * frame->full_wall_dist) / frame->visible_wall_dist;
	frame->ratio = frame->visible_wall_dist / frame->full_wall_dist;
	frame->tex_mult = frame->full_wall_dist / tex->w;
	if (frame->left.wall == frame->right.wall)
	{
		// frame->wall_fract_len = get_distance(frame->left.wall->x0, frame->left.l_pt) / frame->full_wall_dist;
		frame->wall_fract_len = frame->full_wall_len 
			* get_distance(frame->left.wall->x0, frame->left.l_pt)
			/ frame->full_wall_dist;
	}
}

// void	calc_distances(t_frame *frame, t_texture *tex)
// {
// 	frame->l_perp_dist = fabs(frame->left.l_pt.x + 
// 		frame->left.l_pt.y) * SQR2;
// 	frame->r_perp_dist = fabs(frame->left.r_pt.x + 
// 		frame->left.r_pt.y) * SQR2;
// 	frame->wall_x1 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
// 		frame->l_perp_dist) * frame->left.l_pt.x);
// 	frame->wall_x2 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
// 		frame->r_perp_dist) * frame->left.r_pt.x);
// 	frame->visible_wall_dist = get_distance(frame->left.l_pt, frame->left.r_pt);
// 	frame->full_wall_dist = get_distance(frame->left.wall->x0, frame->left.wall->next->x0);
// 	frame->screen_wall_len = frame->wall_x2 - frame->wall_x1;
// 	frame->full_wall_len = frame->screen_wall_len * (frame->full_wall_dist / frame->visible_wall_dist);
// 	frame->tex_mult = frame->full_wall_dist / tex->w;
// 	if (frame->left.wall == frame->right.wall)
// 	{
// 		frame->wall_fract_len = frame->full_wall_len
// 			* get_distance(frame->left.wall->x0, frame->left.l_pt) 
// 			/ frame->full_wall_dist;
// 	}
// 	frame->wall_h_l = SCREEN_HEIGHT / frame->l_perp_dist * 20;
// 	frame->wall_h_r = SCREEN_HEIGHT / frame->r_perp_dist * 20;
// }

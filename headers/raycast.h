/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/04 16:58:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct		s_ray_fov
{
	t_ray			ray_left;
	t_ray			ray_right;
	t_xy			left_point;
	t_xy			right_point;
	t_point			*left_wall;
	t_point			*right_wall;
}					t_ray_fov;


t_ray_fov			get_fov_points(t_point *plgn, t_home *home, t_player *plr, int i);
void				calc_intersection(t_point *pgon, t_point *first, t_ray *ray,
						t_intersection *sect);
t_xy				line_intersection(t_intersection *sect);
void				get_left_point(t_point *start, t_player *plr, t_ray_fov *fov, int offset);
t_xy				get_right_point(t_point *p0, t_point *start, t_player *plr);
void				scan_lines(t_point *point, t_point *start, t_player *plr, t_home *home);
void				scan_fov(t_home *home, t_player *plr, int idx, int max_fov);



#endif

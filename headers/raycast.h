/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/22 09:30:12 by jnivala          ###   ########.fr       */
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
	t_point			*wall;
}					t_ray_fov;


float				get_distance(t_xy p1, t_xy p2);
t_ray_fov			get_fov_points(t_point *plgn, t_home *home, t_player *plr, int i);
void				calc_intersection(t_point *pgon, t_point *first, t_ray *ray,
						t_intersection *sect);
t_xy				line_intersection(t_intersection *sect);
int					get_left_point(t_point *start, t_ray_fov *fov, t_frame *frame, int walls);
int					get_right_point(t_point *start, t_ray_fov *fov, t_frame *frame, int walls);
void				continue_from_next_point(t_point *start, t_ray_fov *fov, t_frame *frame);
void				scan_fov(t_home *home, t_frame *frame);
void				setup_frame(t_frame *frame, t_frame *new_frame, float fov_angle, int idx);
int					check_connection(t_point *point, t_frame *frame);
int					check_if_portal(t_point *point, t_frame *frame);
int					check_if_same_point(float current_angle, t_ray_fov *fov);
void				continue_from_last_sector(t_point *start, t_ray_fov *fov, t_frame *frame);
int					calc_visible_walls(t_sector *sector);
float				ceil_to_pixel(float nb);


#endif

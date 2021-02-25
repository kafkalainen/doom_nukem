/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/23 12:41:57 by jnivala          ###   ########.fr       */
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

typedef struct		s_frame
{
	int				idx;
	int				max_fov;
	int				offset;
	double			min_step;
	int				old_idx;
	SDL_Surface		*draw_surf;
	t_xy			plr_offset;
	float			pxl_offset;
	t_ray_fov		left;
	t_ray_fov		right;
}					t_frame;

float				get_distance(t_xy p1, t_xy p2);
t_ray_fov			get_fov_points(t_point *plgn, t_home *home, t_player *plr, int i);
void				calc_intersection(t_point *pgon, t_ray *ray, t_intersection *sect);
t_xy				line_intersection(t_intersection *sect);
int					get_left_point(t_point *start, t_ray_fov *fov, t_frame *frame, int walls);
int					get_right_point(t_point *start, t_ray_fov *fov, t_frame *frame, int walls);
void				continue_from_next_point(t_ray_fov *fov);
void				scan_fov(t_home *home, t_frame *frame, t_player *plr);
void				setup_frame(t_frame *frame, t_frame *new_frame, int current_pxl, int idx);
int					check_connection(t_point *point, t_frame *frame);
int					check_if_portal(t_point *point);
int					check_if_same_point(int current_pxl, t_ray_fov *fov);
int					check_if_same_wall(t_xy a, t_xy b, t_xy right_point);
void				continue_from_last_sector(t_point *start, t_ray_fov *fov, t_frame *frame);
int					calc_visible_walls(t_sector *sector);
float				ceil_to_pixel(float nb);
void				ft_draw_wall(t_xy left, t_xy right, t_frame *frame, int wall_len, int color, t_home *home, t_player *plr);
int					tex_ft_draw_wall(t_xy left, t_xy right, t_frame *frame, int wall_len, t_texture *tex, t_home *home, t_player *plr);
void				tex_scan_fov(t_home *home, t_frame *frame, t_player *plr);

#endif

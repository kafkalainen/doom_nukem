/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/02 14:05:55 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct		s_ray_pt
{
	t_ray			ray_l;
	t_ray			ray_r;
	t_xy			l_pt;
	t_xy			r_pt;
	t_point			*wall;
}					t_ray_pt;

typedef struct		s_frame
{
	int				idx;
	int				max_fov;
	int				offset;
	float			min_step;
	int				old_idx;
	SDL_Surface		*draw_surf;
	t_xy			plr_offset;
	float			pxl_offset;
	t_ray_pt		left;
	t_ray_pt		right;
	float			wall_x1;
	float			wall_x2;
	float			l_perp_dist;
	float			r_perp_dist;
	float			wall_len;
	float			wall_h_l;
	float			wall_h_r;
}					t_frame;

float				get_distance(t_xy p1, t_xy p2);
void				calc_intersection(t_point *pgon, t_ray *ray, t_intersection *sect);
t_xy				line_intersection(t_intersection *sect);
void				get_wall_pts(t_frame *frame, int walls, int current_pxl);
void				setup_frame(t_frame *frame, t_frame *new_frame, int current_pxl, int idx);
int					check_connection(t_point *point, t_frame *frame);
int					check_if_portal(t_point *point);
int					check_if_same_pt(int current_pxl, t_ray_pt *fov);
void				continue_from_last_sector(t_point *start, t_ray_pt *fov, t_frame *frame);
void				draw_wall(t_frame *frame, t_texture *tex, t_home *home, t_player *plr);
void				scan_fov(t_home *home, t_frame *frame, t_player *plr, int current_pxl);
void				ft_calc_distances(t_frame *frame);

#endif

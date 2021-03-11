/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/11 13:23:41 by jnivala          ###   ########.fr       */
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
	t_xyz			top_left;
	t_xyz			top_right;
	t_xyz			bottom_left;
	t_xyz			bottom_right;
	float			wall_x1;
	float			wall_x2;
	float			full_wall_dist;
	float			visible_wall_dist;
	float			l_perp_dist;
	float			r_perp_dist;
	float			wall_fract_len;
	float			screen_wall_len;
	float			full_wall_len;
	float			wall_h_l;
	float			wall_h_r;
	float			tex_mult;
	float			ratio;
}					t_frame;

float				get_distance(t_xy p1, t_xy p2);
void				calc_intersection(t_point *pgon, t_ray *ray, t_intersection *sect);
t_xy				line_intersection(t_intersection *sect);
void				calc_intersection_raw(t_point *pgon, t_ray *ray, t_intersection *sect);
t_xy				line_intersection_raw(t_intersection *sect);
void				get_wall_pts(t_frame *frame, int walls, int current_pxl);
void				setup_frame(t_frame *frame, t_frame *new_frame, int current_pxl, int idx);
int					check_connection(t_point *point, t_frame *frame);
int					check_if_portal(t_point *point);
int					check_if_same_pt(int current_pxl, t_ray_pt *fov);
void				continue_from_last_sector(t_point *start, t_ray_pt *fov, t_frame *frame);
void				draw_ground(t_player *plr, t_frame *frame, t_home *home);
void				draw_wall(t_frame *frame, t_texture *tex, t_home *home, t_player *plr);
int					draw_tex_line(t_xy start, t_xy end, 
								t_texture *tex, SDL_Surface *surf);
t_texture			*get_tex(int idx, t_texture	**textures);
void				scan_fov(t_home *home, t_frame *frame, t_player *plr, int current_pxl);
void				calc_distances(t_frame *frame, t_texture *tex, t_player *plr);
void				draw_segment(t_frame *frame, t_texture *tex, 
								t_home *home, t_player *plr);

#endif

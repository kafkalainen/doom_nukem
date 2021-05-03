/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/03 15:26:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct s_ray_pt
{
	t_xy			l_pt;
	t_xy			r_pt;
	t_point			*wall;
}					t_ray_pt;

typedef struct s_plgn
{
	t_xyz			top_left;
	t_xyz			top_right;
	t_xyz			bottom_left;
	t_xyz			bottom_right;
}					t_plgn;

typedef struct s_frame
{
	int				idx;
	int				max_fov;
	int				offset;
	int				draw_top;
	int				draw_middle;
	int				draw_bottom;
	float			min_step;
	int				old_idx;
	Uint32			*buffer;
	float			pxl_offset;
	t_ray_pt		left;
	t_ray_pt		right;
	t_plgn			inner_box;
	t_plgn			outer_box;
	t_plgn			top_uv;
	t_plgn			middle_uv;
	t_plgn			bottom_uv;
	t_xyz			ground_uv_t_l;
	t_xyz			ground_uv_t_r;
	t_xyz			ground_uv_b_l;
	t_xyz			ground_uv_b_r;
	t_xyz			uv_step;
	t_xyz			ground_uv_step;
	t_xyz			step_inner_top;
	t_xyz			step_inner_bot;
	t_xyz			step_outer_top;
	t_xyz			step_outer_bot;
	float			full_wall_dist;
	float			visible_wall_dist;
	float			unvisible_l_side;
	float			screen_wall_len;
	float			tex_mult;
	float			ratio;
	int				pitch;
}					t_frame;

enum e_lines
{
	colinear = 0,
	clockwise = 1,
	c_clockwise = 2,
};

void		calc_dimensions(t_frame *frame, t_player *plr, t_home *home);
void		calc_ground_texels(t_sector *sector, t_frame *frame);
void		calc_intersection(t_point *pgon, t_ray *ray,
				t_intersection *sect);
void		calc_sector_texels(t_sector *sector);
void		calc_wall_texels(t_frame *frame, int tex_width);
int			check_connection(t_point *point, t_frame *frame);
int			check_if_portal(t_point *point);
int			check_if_same_pt(int *current_pxl, t_ray_pt *fov);
int			check_if_lseg_intersects(t_point *p0, t_xy *pos, t_xy *dir);
void		continue_from_last_sector(t_point *start, t_ray_pt *fov,
				t_frame *frame);
void		draw_ground(t_player *plr, t_frame *frame, t_home *home);
void		draw_segment(t_frame *frame, t_home *home, t_player *plr);
int			draw_tex_line(t_xy start, t_xy end,
				t_texture *tex, SDL_Surface *surf);
void		draw_vertically(t_frame *frame, t_sector *sector,
	t_texture *wall_tex);
void		draw_wall(t_frame *frame, t_texture *tex, t_home *home,
				t_player *plr);
int			get_next_wall_tex(t_point **current_head, int nbr_of_walls);
t_texture	*get_tex(int idx, t_texture	**textures);
void		get_wall_pts(t_frame *frame, int walls, int current_pxl);
t_xy		line_intersection(t_intersection *sect);
t_xy		line_intersection_raw(t_intersection *sect);
void		scan_fov(t_home *home, t_frame *frame, t_player *plr,
				int current_pxl);
void		setup_frame(t_frame *frame, t_frame *new_frame,
				int current_pxl, int idx);
void		step_one(t_frame *frame);

#endif

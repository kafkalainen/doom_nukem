/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/09 13:21:26 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

typedef struct s_fov
{
	t_xy			left;
	t_xy			right;
	t_xy			pos;
	int				cur_sector;
}				t_fov;

/*
**	raster_queue: Individual raster queues given to each thread
**	in multithreading.
**	triangles_in_view: Triangles that are in player's view.
**	transformed: Triangles that are in front of the player,
**	but need to be validated that are they visible.
**	buffer: Array of pixels, that are eventually drawn to the screen.
**	Has also information about lightness of the screen, and width and
**	height property.
**	depth_buffer: Depth buffer is array of depths corresponding each
**	pixel on the screen, to know whether we can still draw there.
**	sector_buffer: Buffer for sectors, so draw sector function knows
**	to draw sectors.
**	fov: field of vision, with two rays that are casted from the
**	position of the player.
**	viewport: sides of the viewport, to which triangles are clipped,
**	including near and far plane.
**	idx: current sector we are in.
*/
typedef struct s_frame
{
	t_raster_queue	**raster_queue;
	t_raster_queue	*triangles_in_view;
	t_raster_queue	*transformed;
	t_buffer		buffer;
	float			*depth_buffer;
	t_fov			fov;
	t_sides			viewport;
	int				idx;
}				t_frame;

enum			e_lines
{
	colinear = 0,
	clockwise = 1,
	c_clockwise = 2,
};

void			add_ceiling(t_home *home, t_frame *frame, t_player *plr);
void			add_ground(t_home *home, t_frame *frame, t_player *plr);
void			add_walls(t_home *home, t_frame *frame, t_player *plr);
void			add_entities(t_home *home, t_frame *frame, t_player *plr);
void			add_projectiles(t_home *home, t_frame *frame, t_player *plr);
void			assign_booleans_for_fov(t_bool *res_left, t_bool *res_right,
					t_fov fov, t_wall *wall);
void			calc_sector_bounds(t_sector *sector);
void			calc_extra_walls(t_home *home);
t_xy			calculate_centroid(t_sector *sector);
float			calculate_lumel_offset(float from, float to, float t);
t_uvz			calculate_texel_offset(t_uvz from, t_uvz to, float t);
void			calculate_triangle(t_frame *frame, t_triangle *tri,
					t_texture *tex);
t_bool			check_if_hull(t_wall *wall);
t_bool			check_if_portal(t_wall *point);
int				check_if_lseg_intersects(t_xy *p0, t_xy *p1, t_xy *pos,
					t_xy *dir);
t_bool			check_if_already_been_in_this_sector(int cur_sector,
					int *sector_list, int nb_of_sectors);
t_bool			check_if_facing_player(t_bool left, t_bool right, t_wall *wall,
					t_fov fov);
t_bool			check_if_moved_through_portal(int *cur_sector,
					t_xyz pos, t_home *home);
t_bool			check_if_too_close_to_a_door(t_wall *door, float width,
					t_xyz pos, t_xyz dir);
t_wall			*check_if_too_close_to_walls(t_sector *sector, float width,
					t_xyz pos, t_xyz dir);
int				check_intersection(t_wall *p0, t_xy pos, t_xy dir);
void			*clip_to_viewport_edges(void *args);
Uint32			colour_scale(Uint32 hex, float lumel, float lightness,
					float fog);
t_raster_queue	*create_raster_queue(size_t capacity);
t_raster_queue	*delete_raster_queue(t_raster_queue **queue);
int				dequeue(t_raster_queue *queue);
void			draw_queue_empty(t_frame *frame, t_home *home,
					t_player *plr, int *idx);
int				enqueue_to_raster(t_raster_queue *queue, t_triangle *item);
void			free_queues(t_frame *frame);
int				front(t_raster_queue *queue, t_triangle *triangle);
int				get_next_wall_tex(t_wall **current_head, int nbr_of_walls);
t_texel			*get_tex(int idx, t_texture	**textures);
float			get_wall_height(float left_ground, float right_ground,
					float left_ceiling, float right_ceiling);
t_wall			*get_portal_by_idx(int idx, t_sector *sector);
t_bool			is_triangle_visible(t_triangle *viewed_tri, t_xyz pos);
int				orientation_of_three_points(t_xy a, t_xy b, t_xy c);
int				point_is_on_the_lseg(t_xy a, t_xy c, t_xy b);
t_triangle		project_to_screen_space(t_triangle *src, t_xyz view_offset,
					t_xyz scale);
void			quick_reset_queue(t_raster_queue *queue);
int				raster_queue_is_full(t_raster_queue *queue);
int				raster_queue_is_empty(t_raster_queue *queue);
t_triangle		rotate_triangle(t_triangle *src, float angle, char dir);
t_bool			run_tests(t_home *home);
t_triangle		scale_triangle(t_triangle *src, t_xyz scale);
int				scan_fov(t_home *home, t_fov fov, int nb_of_sectors,
					int **sector_list);
void			set_lighting(t_lighting *light, t_triangle *tri);
void			setup_frame(t_fov *new_fov, t_fov *fov, t_wall *wall);
t_bool			ship_part(int type);
void			show_hull(t_triangle *viewed_tri);
void			update_world(t_player *plr, t_home *home, Uint32 delta_time);
t_xyz			translate_point(t_xyz *src, t_xyz translation);
t_triangle		translate_triangle(t_triangle *src, t_xyz translation);

#endif

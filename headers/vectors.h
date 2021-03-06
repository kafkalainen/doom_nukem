/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:23:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/11 12:39:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef unsigned char	t_uchar;

typedef unsigned int	t_uint;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_height
{
	float			ground;
	float			ceiling;
}					t_height;

typedef struct s_screen_xy
{
	int				x;
	int				y;
}					t_screen_xy;

typedef struct s_xy
{
	float			x;
	float			y;
	float			w;
}					t_xy;

typedef struct s_box
{
	t_xy			start;
	t_xy			end;
}					t_box;

typedef struct s_xyz
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_xyz;

typedef struct s_uvz
{
	float			u;
	float			v;
	float			w;
}					t_uvz;

typedef struct s_uv
{
	int				u;
	int				v;
}					t_uv;

typedef struct s_point_location
{
	t_xyz		points_inside[3];
	t_xyz		points_outside[3];
	t_uvz		texels_inside[3];
	t_uvz		texels_outside[3];
	float		lumels_outside[3];
	float		lumels_inside[3];
	int			inside;
	int			outside;
	float		texel_offset;
}					t_point_location;

typedef struct s_triangle
{
	t_xyz			p[3];
	t_uvz			uv[3];
	float			lu[3];
	t_bool			hull;
	int				type;
	t_xyz			normal;
}				t_triangle;

typedef struct s_raster_queue
{
	int			front;
	int			rear;
	int			size;
	int			capacity;
	t_triangle	*array;
}				t_raster_queue;

typedef struct s_m4x4 {
	float	m[4][4];
}				t_m4x4;

typedef struct s_m3x3
{
	float		m[3][3];
}				t_m3x3;

typedef struct s_ray
{
	t_xyz			pos;
	t_xyz			dir;
	t_xyz			plr_pos;
	int				side;
	int				start_sector;
	int				end_sector;
}					t_ray;

typedef struct s_plgn
{
	t_xy			top_left;
	t_xy			top_right;
	t_xy			bottom_left;
	t_xy			bottom_right;
}					t_plgn;

typedef struct s_plane
{
	t_xyz			point;
	t_xyz			normal;
}					t_plane;

typedef struct s_pxl_coords
{
	int				x;
	int				y;
}					t_pxl_coords;

typedef struct s_deltas
{
	int			x;
	int			y;
	float		u;
	float		v;
	float		w;
	float		i;
}				t_deltas;

typedef struct s_sides
{
	t_plane			far;
	t_plane			near;
	t_plane			left;
	t_plane			right;
	t_plane			top;
	t_plane			bottom;
	t_plane			*mid_planes;
	t_xyz			view_offset;
	t_xyz			scale;
}					t_sides;

typedef struct s_planes
{
	t_plane			left;
	t_plane			right;
	t_plane			top;
	t_plane			bottom;
}					t_planes;

typedef struct s_steps
{
	float			denom_dy_a_side;
	float			denom_dy_b_side;
	t_uvz			tex_a_side;
	t_uvz			tex_b_side;
	t_xyz			screen_step_a_side;
	t_xyz			screen_step_b_side;
	float			lumel_step_a_side;
	float			lumel_step_b_side;
	t_uvz			start_uv;
	t_uvz			end_uv;
	t_pxl_coords	start;
	t_pxl_coords	end;
	t_uvz			cur_texel;
	char			current_triangle;
	t_deltas		delta_p0p1;
	t_deltas		delta_p0p2;
	float			start_lu;
	float			end_lu;
	float			offset_step;
	float			offset;
	t_uvz			texel_inv;
	t_uvz			texel_start;
	t_uvz			texel_end;
	t_uvz			delta;
	float			delta_lu;
	float			sub_lu_start;
	float			sub_lu_end;
	float			delta_w;
	int				sub_pixels;
}				t_steps;

/*
** Vector functions
*/

float		interpolate_points(float x0, float x1, float y0, float y1);
t_xyz		inv_z(t_xyz a);
t_xyz		multi_vec_matrix(t_xyz *src, t_m4x4 *x);
t_xy		vec2(float x, float y);
t_xy		vec2_add(t_xy a, t_xy b);
float		vec2_ang(t_xy a, t_xy b);
float		vec2_ang_simple(t_xy a, t_xy b);
float		vec2_cross(t_xy a, t_xy b);
t_xy		vec2_dec(t_xy a, t_xy b);
t_xy		vec2_div(t_xy a, float scalar);
float		vec2_dot(t_xy a, t_xy b);
float		vec2_eucl_dist(t_xy p1, t_xy p2);
float		vec2_mag(t_xy a);
t_xy		vec2_mul(t_xy v, float scalar);
t_xy		vec2_unit_vector(t_xy v);
t_xy		vec2_normal(t_xy p0, t_xy p1);
t_xy		vec2_rot(t_xy v, float angle);
float		vec2_perp_dist(t_xy a);
t_xyz		vec3(float x, float y, float z);
t_xyz		vec3_add(t_xyz a, t_xyz b);
float		vec3_eucl_dist(t_xyz a);
t_xy		vec3_to_vec2(t_xyz a);
float		vec2_distance_from_point_to_line(t_xy *p0, t_xy *p1, t_xy *x0);
t_m4x4		translate_matrix(t_xyz a);
t_m4x4		scaling_matrix(t_xyz a);
t_m4x4		rotation_matrix_x(float angle);
t_m4x4		rotation_matrix_y(float angle);
t_m4x4		rotation_matrix_z(float angle);
t_m4x4		projection_matrix(void);
t_xyz		triangle_normal(t_triangle *triangle);
float		vec3_dot_product(t_xyz a, t_xyz b);
t_xyz		vec3_dec(t_xyz a, t_xyz b);
t_xyz		vec3_unit_vector(t_xyz a);
t_uvz		texel_inv_z(t_uvz a);
void		triangle_inv_z(t_triangle *tri);
t_uvz		uvz_calculate_value_with_delta(float delta_x, t_uvz delta_u,
				t_uvz delta_v);
float		triangle_calculate_average_z(t_triangle *triangle);
t_xyz		vec3_mul(t_xyz a, float multiplier);
t_xyz		vec3_cross_product(t_xyz a, t_xyz b);
t_m4x4		point_at_matrix(t_xyz up, t_xyz forward, t_xyz right,
				t_xyz location);
t_m4x4		inverse_matrix(t_m4x4 *rot_trans_matrix);
t_m4x4		identity_matrix(void);
t_m4x4		multiply_matrix(t_m4x4 *m1, t_m4x4 *m2);
t_triangle	apply_world_matrix(float angle_x, float angle_z,
				t_xyz translation, t_triangle *src);
t_xyz		vec3_div(t_xyz a, float scalar);
t_xyz		vec3_intersection_with_plane(t_plane *plane, t_xyz start, t_xyz end,
				float *texel_offset);
int			clip_to_plane(t_plane *plane, t_triangle *src,
				t_triangle *triangle1, t_triangle *triangle2);
void		initialize_locations(t_point_location *loc);
void		triangle_add(t_triangle *tri, t_xyz	add);
void		invert_view(t_triangle *triangle);
float		vec3_signed_distance_to_plane(t_xyz point, t_xyz plane_normal,
				t_xyz plane_point);
float		area_of_triangle(t_xyz p0, t_xyz p1, t_xyz p2);
t_bool		point_inside_a_triangle_surface(t_xyz p0, t_xyz p1,
				t_xyz p2, t_xyz p);
t_xyz		vec3_intersection_with_ray_and_plane(t_plane *plane,
				t_xyz origo, t_xyz dir);
t_xyz		vec3_calc_vector_average(t_raster_queue	*queue);
t_uvz		texel_mul(t_uvz *texel, float mul);
t_uvz		texel_lerp(t_uvz *texel_start, float steps, t_uvz *delta);
t_uvz		texel_add(t_uvz *a, t_uvz *b);
void		calc_texel(t_uvz *texel, t_uvz *start, float offset,
				t_uvz *end);
void		calc_lumel(float *lumel, float *start, float offset,
				float *end);
t_bool		vec3_check_sidedness(t_xyz p1, t_xyz p2, t_xyz a, t_xyz b);
t_bool		vec3_is_inside_triangle(t_triangle *tri, t_xyz point);
t_bool		vec3_ray_triangle_intersect(t_triangle *tri,
				t_xyz pos, t_xyz dir, t_xyz *isection);
float		vec3_angle(t_xyz to_be_turned, t_xyz compared);
void		initialize_lumels(float *p0, float *p1, float *p2, float init);
float		vec3_ang_axis(t_xyz to_be_turned, t_xyz compared, char axis);
t_m3x3		scaling_matrix_2d(t_xy scale);
t_m3x3		translation_matrix_2d(t_xy translation);
t_m3x3		rotation_matrix_2d(float angle);
t_m3x3		multiply_2d_matrix_with_2d_matrix(t_m3x3 *m1, t_m3x3 *m2);
t_xy		multiply_vec2_with_2d_matrix(t_xy *src, t_m3x3 *x);
t_bool		point_inside_fov(t_xy p0, t_xy p1, t_xy p2, t_xy p);
void		triangle_div(t_triangle *projected);
float		vec2_get_distance_squared(t_xy pt0, t_xy pt1);
t_bool		vec3_ray_intersects_triangle(t_triangle *inTriangle,
				t_xyz ray_origin, t_xyz ray_vector, t_xyz *isection);
float		vec2_determine_rotation(t_xy v0, t_xy v1, char axis);
#endif

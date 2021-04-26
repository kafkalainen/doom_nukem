/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:44:38 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/26 15:40:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_screen_xy
{
	int				x;
	int				y;
}					t_screen_xy;

typedef struct s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef t_xy	t_range;

typedef struct s_xyz
{
	float			x;
	float			y;
	float			z;
}					t_xyz;

typedef struct s_ray
{
	t_xy			pos;
	t_xy			dir;
	t_xy			cutpoint;
}					t_ray;

typedef struct s_maxpoints
{
	t_xy			left;
	t_xy			right;
}					t_maxpoints;

/*
** Vector functions
*/

float	interpolate_points(float x0, float x1, float y0, float y1);
t_xyz	inv_z(t_xyz a);
t_xy	vec2(float x, float y);
t_xy	vec2_add(t_xy a, t_xy b);
float	vec2_ang(t_xy a, t_xy b);
float	vec2_cross(t_xy a, t_xy b);
t_xy	vec2_dec(t_xy a, t_xy b);
float	vec2_dot(t_xy a, t_xy b);
float	vec2_eucl_dist(t_xy p1, t_xy p2);
float	vec2_mag(t_xy a);
t_xy	vec2_mul(t_xy v, float scalar);
t_xy	vec2_norm(t_xy v);
t_xy	vec2_normal(t_xy p0, t_xy p1);
t_xy	vec2_rot(t_xy v, float angle);
float	vec2_perp_dist(t_xy a);
t_xyz	vec3(float x, float y, float z);
t_xyz	vec3_add(t_xyz a, t_xyz b);
t_xy	vec3_to_vec2(t_xyz a);

#endif

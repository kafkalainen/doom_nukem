/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:44:38 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/19 14:36:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct		s_screen_xy
{
	int				x;
	int				y;
}					t_screen_xy;

typedef struct		s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef t_xy		t_range;

typedef struct		s_xyz
{
	float			x;
	float			y;
	float			z;
}					t_xyz;

typedef struct		s_ray
{
	t_xy			pos;
	t_xy			dir;
	t_xy			cutpoint;
}					t_ray;

typedef struct		s_maxpoints
{
	t_xy			left;
	t_xy			right;
}					t_maxpoints;

/*
** Vector functions
*/

t_xy			vec2(float x, float y);
t_xy			vec2_add(t_xy a, t_xy b);
t_xy			vec2_dec(t_xy a, t_xy b);
t_xy			vec2_rot(t_xy v, float angle);
t_xy			vec2_norm(t_xy v);
t_xy			vec2_mul(t_xy v, float scalar);
float			vec2_dot(t_xy a, t_xy b);
float			ft_map(float in, t_range from, t_range to);
float			vec2_dot(t_xy a, t_xy b);
float			vec2_mag(t_xy a);
float			vec2_angle(t_xy a, t_xy b);

#endif

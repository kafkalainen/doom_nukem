/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:44:38 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/20 13:44:38 by tmaarela         ###   ########.fr       */
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
	double			x;
	double			y;
}					t_xy;

typedef t_xy		t_range;

typedef struct		s_xyz
{
	double			x;
	double			y;
	double			z;
}					t_xyz;

/*
** Vector functions
*/

t_xy			vec2(double x, double y);
t_xy			vec2_add(t_xy a, t_xy b);
t_xy			vec2_dec(t_xy a, t_xy b);
t_xy			vec2_rot(t_xy v, double angle);
t_xy			vec2_norm(t_xy v);
t_xy			vec2_mul(t_xy v, double scalar);
double			vec2_dot(t_xy a, t_xy b);
double			ft_map(double in, t_range from, t_range to);

#endif

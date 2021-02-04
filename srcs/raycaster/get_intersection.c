/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:05:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/04 10:16:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

float	vec2_cross(t_xy u, t_xy v)
{
	return (u.x * v.y - u.y * v.x);
}

t_xy	get_intersection(t_point *pgon, t_point *first, t_ray *ray,
					t_intersection *sect)
{
	t_xy	p;
	t_xy	v;
	t_xy	q;
	t_xy	u;
	t_point	*v_0;
	float	cross;
	t_xy	point;

	p = pgon->x0;
	v_0 = loop_list(first, pgon->next);
	v = v_0->x0;
	q = ray->pos;
	u = ray->dir;
	cross = vec2_cross(u, v);
	if (cross == 0)
		return vec2(-1, -1);
	// find b = (Q1-P1) x u
	cross = vec2_cross(vec2_dec(q, p), u);      // cross product
	// find t = (b.a)/(a.a) = ((Q1-P1) x u) .(v x u) / (v x u) . (v x u)
	point = vec2_add(p, vec2_mul(v, cross));
	// find intersection point
	// substitute t to line1
	return (point);
}

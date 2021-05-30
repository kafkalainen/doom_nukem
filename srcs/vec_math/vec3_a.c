/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:39:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/30 19:02:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xyz	vec3(float x, float y, float z)
{
	float	w;

	w = 1.0f;
	return ((t_xyz){x, y, z, w});
}

t_xyz	vec3_add(t_xyz a, t_xyz b)
{
	return ((t_xyz){a.x + b.x, a.y + b.y, a.z + b.z, 1.0f});
}

t_xy	vec3_to_vec2(t_xyz a)
{
	return ((t_xy){a.x, a.y});
}

float	vec3_eucl_dist(t_xyz a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_xyz	inv_z(t_xyz a)
{
	a.z = 1.0f / a.z;
	a.x = a.x * a.z;
	a.y = a.y * a.z;
	return (a);
}

t_uvz	texel_inv_z(t_uvz a)
{
	a.w = 1.0f / a.w;
	a.u = a.u * a.w;
	a.v = a.v * a.w;
	return (a);
}

void	triangle_inv_z(t_triangle *tri)
{
	tri->uv[0].w = 1.0f / tri->p[0].w;
	tri->uv[1].w = 1.0f / tri->p[1].w;
	tri->uv[2].w = 1.0f / tri->p[2].w;
	tri->uv[0].u = tri->uv[0].w * tri->uv[0].u;
	tri->uv[1].u = tri->uv[1].w * tri->uv[1].u;
	tri->uv[2].u = tri->uv[2].w * tri->uv[2].u;
	tri->uv[0].v = tri->uv[0].w * tri->uv[0].v;
	tri->uv[1].v = tri->uv[1].w * tri->uv[1].v;
	tri->uv[2].v = tri->uv[2].w * tri->uv[2].v;
}

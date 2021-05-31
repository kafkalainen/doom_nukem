/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 09:33:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/31 17:51:03 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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

void	triangle_add(t_triangle *triangle, t_xyz add)
{
	triangle->p[0] = vec3_add(triangle->p[0], add);
	triangle->p[1] = vec3_add(triangle->p[1], add);
	triangle->p[2] = vec3_add(triangle->p[2], add);
}

void	invert_view(t_triangle *triangle)
{
	triangle->p[0].x *= -1.0f;
	triangle->p[0].y *= -1.0f;
	triangle->p[1].x *= -1.0f;
	triangle->p[1].y *= -1.0f;
	triangle->p[2].x *= -1.0f;
	triangle->p[2].y *= -1.0f;
}

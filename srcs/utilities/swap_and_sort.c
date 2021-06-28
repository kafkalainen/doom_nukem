/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_and_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 16:37:52 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/27 16:32:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	swap_float(float *f0, float *f1)
{
	float swap;

	swap = *f0;
	*f0 = *f1;
	*f1 = swap;
}

void	swap_int(int *i0, int *i1)
{
	int swap;

	swap = *i0;
	*i0 = *i1;
	*i1 = swap;
}

void	swap_xyz(t_xyz *p0, t_xyz *p1)
{
	t_xyz	swap;

	swap.x = p0->x;
	swap.y = p0->y;
	swap.z = p0->z;
	p0->x = p1->x;
	p0->y = p1->y;
	p0->z = p1->z;
	p1->x = swap.x;
	p1->y = swap.y;
	p1->z = swap.z;
}

void	swap_uvz(t_uvz *p0, t_uvz *p1)
{
	t_uvz	swap;

	swap.u = p0->u;
	swap.v = p0->v;
	swap.w = p0->w;
	p0->u = p1->u;
	p0->v = p1->v;
	p0->w = p1->w;
	p1->u = swap.u;
	p1->v = swap.v;
	p1->w = swap.w;
}

void	sort_vertices(t_triangle *tri)
{
	if ((int)tri->p[1].y < (int)tri->p[0].y)
	{
		swap_xyz(&tri->p[0], &tri->p[1]);
		swap_uvz(&tri->uv[0], &tri->uv[1]);
		swap_float(&tri->i[0], &tri->i[1]);
	}
	if ((int)tri->p[2].y < (int)tri->p[0].y)
	{
		swap_xyz(&tri->p[0], &tri->p[2]);
		swap_uvz(&tri->uv[0], &tri->uv[2]);
		swap_float(&tri->i[0], &tri->i[2]);
	}
	if ((int)tri->p[2].y < (int)tri->p[1].y)
	{
		swap_xyz(&tri->p[1], &tri->p[2]);
		swap_uvz(&tri->uv[1], &tri->uv[2]);
		swap_float(&tri->i[1], &tri->i[2]);
	}
}

void	swap_sides(t_steps *steps)
{
	if (steps->start_x > steps->end_x)
	{
		swap_int(&steps->start_x, &steps->end_x);
		swap_uvz(&steps->start_uv, &steps->end_uv);
		swap_float(&steps->start_i, &steps->end_i);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_left_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:33:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/08 08:30:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

/*
** TODO:
** - Make linked list into a loop.
** - Function that checks left point is our portal connected to the same sector.
** - Simplify get_left_point just to check the intersection left point.
*/
void		get_left_point(t_point *start, t_ray_fov *fov, t_frame *frame)
{
	t_ray			ray;
	t_intersection	sect;
	t_point			*p0;

	ray.pos = vec2(0, 0);
	ray.dir = vec2(0.785389163, 0.785389163);
	if (frame->offset != 0 || frame->idx == frame->old_idx)
	{
		fov->left_wall = fov->left_wall->next;
		fov->left_point = fov->left_wall->x0;
		fov->right_point = fov->left_wall->next->x0;
		return ;
	}
	p0 = start;
	while (p0)
	{
		if (p0->x0.y >= 0 || p0->next->x0.y >= 0)
		{
			calc_intersection(p0, start, &ray, &sect);
			fov->left_point = line_intersection(&sect);
			if (fov->left_point.y != -1)
				break ;
		}
		p0 = p0->next;
	}
	fov->left_wall = p0;
	fov->right_point = fov->left_wall->next->x0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_left_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:33:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/05 11:51:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

/*
** Counter-clockwise
** Segfault line 43
** Segfault happens due line-line intersection will not find intersection point.
** Clockwise
** Infinite loop
** NOTE:
** Plr dir is a constant, we don't have to count it any longer. Use enum or define instead.
** If(wall_index == frame_idx) skip point.
*/
void		get_left_point(t_point *start, t_ray_fov *fov, int offset)
{
	t_ray			ray;
	t_intersection	sect;
	t_point			*p0;

	ray.pos = vec2(0, 0);
	ray.dir = vec2(0.70710678118, 0.70710678118);
	if (offset != 0)
	{
		fov->left_wall = loop_list(start, fov->left_wall->next);
		fov->left_point = fov->left_wall->x0;
		fov->right_point = loop_list(start, fov->left_wall->next)->x0;
		return ;
	}
	p0 = start;
	while (p0)
	{
		if (p0->x0.y >= 0 || loop_list(start, p0->next)->x0.y >= 0)
		{
			calc_intersection(p0, start, &ray, &sect);
			fov->left_point = line_intersection(&sect);
			if (fov->left_point.y != -1)
				break ;
		}
		p0 = loop_list(start, p0->next);
	}
	fov->left_wall = p0;
	fov->right_point = loop_list(start, fov->left_wall->next)->x0;
}

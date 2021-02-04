/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_left_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:33:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/04 17:05:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		get_left_point(t_point *start, t_player *plr, t_ray_fov *fov, int offset)
{
	t_ray			ray;
	t_intersection	sect;
	t_point			*p0;

	ray.pos = vec2(0, 0);
	ray.dir = vec2_rot(plr->dir, DEG_TO_RAD * -FOV * 0.5);
	p0 = start;
	if (offset != 0)
	{
		fov->left_wall = loop_list(start, p0->next);
		fov->left_point = fov->left_wall->x0;
		fov->right_point = loop_list(start, fov->left_wall->next)->x0;
		return ;
	}
	while (p0)
	{
		if (p0->x0.y >= 0)
		{
			calc_intersection(p0, start, &ray, &sect);
			fov->left_point = line_intersection(&sect);
			if (fov->left_point.y != -1)
				break ;
		}
		p0 = p0->next;
	}
	fov->left_wall = p0;
	fov->left_point = fov->left_wall->x0;
	fov->right_point = loop_list(start, fov->left_wall->next)->x0;
}

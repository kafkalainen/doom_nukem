/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_right_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:29:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/18 12:44:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int		get_right_point(t_point *start, t_ray_fov *fov, t_frame *frame, int walls)
{
	t_ray			ray;
	t_intersection	sect;
	t_point			*p0;

	ray.pos = vec2(0, 0);
	ray.dir = vec2_rot(vec2(0, 1), -frame->max_fov);
	p0 = start;
	while (walls)
	{
		if (p0->x0.y >= 0 || p0->next->x0.y >= 0)
		{
			calc_intersection(p0, start, &ray, &sect);
			fov->right_point = line_intersection(&sect);
			if (fov->right_point.y != -1)
				break ;
		}
		p0 = p0->next;
		walls--;
	}
	fov->left_wall = p0;
	fov->left_point = fov->left_wall->x0;
	return (1);
}

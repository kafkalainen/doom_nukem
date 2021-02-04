/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:59:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/04 17:07:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"


static int		offset = 0;

void			scan_fov(t_home *home, t_player *plr, int idx, int max_fov)
{
	t_ray_fov	fov;
	float		angle;
	int			new_fov;

	while (offset < max_fov)
	{
		get_left_point(home->sectors[idx]->points, plr, &fov, offset);
		angle = vec2_angle(fov.left_point, fov.right_point);
		if ((new_fov = SCREEN_WIDTH * angle / (FOV * DEG_TO_RAD) < max_fov))
		{
			if (fov.left_wall->idx > 0)
				scan_fov(home, plr, fov.left_wall->idx, new_fov);
			ft_draw_line(
				vec2_add(fov.left_point, home->offset),
				vec2_add(fov.right_point, home->offset),
				green,
				home->draw_surf
			);
			offset = new_fov + offset;
		}
	}
}

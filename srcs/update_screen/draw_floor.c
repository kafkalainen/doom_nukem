/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:33:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/22 13:30:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			draw_fov_floor(t_home *home, t_player *plr)
{
	t_ray_floor	horizontal;
	int			j;

	j = 0;
	horizontal.plane = vec2_rot(plr->dir, FOV * DEG_TO_RAD);
	horizontal.left = vec2_dec(plr->dir, horizontal.plane);
	horizontal.right = vec2_add(plr->dir, horizontal.plane);
	while (j < SCREEN_HEIGHT)
	{
		//draw_world_floor(j, plr, home, horizontal);
		j++;
	}
}

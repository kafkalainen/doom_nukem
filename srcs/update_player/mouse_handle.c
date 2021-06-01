/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:55:46 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/01 08:14:06 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	mouse_handle(t_player *plr, t_home *home, SDL_Event *e)
{
	(void)home;
	if (e->type == SDL_MOUSEMOTION)
	{
		plr->dir.x += -e->motion.xrel * DEG_TO_RAD * 0.1;
		plr->dir.y += -e->motion.xrel * DEG_TO_RAD * 0.1;
		plr->yaw -= -e->motion.xrel * 0.01f;
		if (plr->dir.x > TWO_PI)
			plr->dir = (t_xy){0.0f, 0.0f};
		if (plr->dir.x < 0)
			plr->dir = (t_xy){TWO_PI, TWO_PI};
		// transform_world_view(home, -e->motion.xrel * DEG_TO_RAD * 0.1);
		plr->pitch += -e->motion.yrel * 0.01f;
		// plr->pitch = ft_fmin(ft_fmax((plr->pitch - e->motion.yrel), 0), 480);
	}
}

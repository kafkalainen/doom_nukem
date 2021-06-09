/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:55:46 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/09 10:24:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	mouse_handle(t_player *plr, SDL_Event *e)
{
	if (e->type == SDL_MOUSEMOTION)
	{
		plr->dir.x += -e->motion.xrel * DEG_TO_RAD * 0.1;
		plr->dir.y += -e->motion.xrel * DEG_TO_RAD * 0.1;
		plr->yaw += e->motion.xrel * 0.01f;
		if (plr->yaw > PI)
			plr->yaw = PI;
		if (plr->yaw < -PI)
			plr->yaw = -PI;
		if (plr->dir.x < 0)
			plr->dir = (t_xy){0.0f, 0.0f};
		if (plr->dir.x > TWO_PI)
			plr->dir = (t_xy){TWO_PI, TWO_PI};
		plr->pitch += e->motion.yrel * 0.01f;
		if (plr->pitch < -1.553343)
			plr->pitch = -1.553343;
		if (plr->pitch > 1.553343)
			plr->pitch = 1.553343;
		printf("%f\n", plr->yaw);
	}
}

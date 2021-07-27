/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:55:46 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/15 15:53:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	mouse_handle(t_player *plr, SDL_Event *e)
{
	if (e->type == SDL_MOUSEMOTION)
	{
		plr->dir.x += -e->motion.xrel * DEG_TO_RAD * 0.1;
		plr->dir.y += -e->motion.xrel * DEG_TO_RAD * 0.1;
		plr->hud.vm_rx += -e->motion.xrel * DEG_TO_RAD * 3;
		plr->yaw += e->motion.xrel * 0.01f;
		if (plr->yaw > TWO_PI)
			plr->yaw = 0.0f;
		if (plr->yaw < 0.0f)
			plr->yaw = TWO_PI;
		if (plr->dir.x < 0)
			plr->dir = (t_xy){0.0f, 0.0f};
		if (plr->dir.x > TWO_PI)
			plr->dir = (t_xy){TWO_PI, TWO_PI};
		plr->pitch += e->motion.yrel * 0.01f;
		plr->hud.vm_ry += -e->motion.yrel * DEG_TO_RAD * 3;
		if (plr->pitch < -1.553343)
			plr->pitch = -1.553343;
		if (plr->pitch > 1.553343)
			plr->pitch = 1.553343;
	}
	if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_RIGHT)
		plr->input.jetpack = 1;
	if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_RIGHT)
		plr->input.jetpack = 0;
}

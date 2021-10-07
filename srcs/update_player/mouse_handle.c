/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:55:46 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/07 13:02:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	mouse_button_handle(t_player *plr, SDL_Event *e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
		plr->input.shoot = 1;
	if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT)
		plr->input.shoot = 0;
	if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_RIGHT)
		plr->input.jetpack = 1;
	if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_RIGHT)
		plr->input.jetpack = 0;
}

void	mouse_handle(t_player *plr, SDL_Event *e)
{
	if (plr->input.mouse && e->type == SDL_MOUSEMOTION && plr->dead == 0)
	{
		plr->dir.x += -e->motion.xrel * 0.00174532925f;
		plr->dir.y += -e->motion.xrel *  0.00174532925f;
		plr->hud.vm_rx += -e->motion.xrel * 0.005235988f;
		plr->yaw += -e->motion.xrel * 0.01f;
		if (plr->yaw > TWO_PI)
			plr->yaw = 0.0f;
		if (plr->yaw < 0.0f)
			plr->yaw = TWO_PI;
		if (plr->dir.x < 0)
			plr->dir = vec2(0.0f, 0.0f);
		if (plr->dir.x > TWO_PI)
			plr->dir = vec2(TWO_PI, TWO_PI);
		plr->pitch += -e->motion.yrel * 0.01f;
		plr->hud.vm_ry += -e->motion.yrel * 0.005235988f;
		if (plr->pitch < -1.4)
			plr->pitch = -1.4;
		if (plr->pitch > 1.553343)
			plr->pitch = 1.553343;
	}
	if (plr->input.mouse)
		mouse_button_handle(plr, e);
}

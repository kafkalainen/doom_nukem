/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:55:46 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/01 10:23:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	mouse_handle_win(t_player *plr)
{
	SDL_Event	me;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (me.type == SDL_MOUSEMOTION)
		plr->dir = vec2_rot(plr->dir, DEG_TO_RAD * me.motion.xrel);
}

void	mouse_handle_unix(t_player *plr, t_home *home)
{
	t_xy		mouse;
	t_screen_xy	mouse_screen;

	SDL_ShowCursor(SDL_DISABLE);
	SDL_CaptureMouse(SDL_TRUE);
	SDL_GetMouseState(&mouse_screen.x, &mouse_screen.y);
	mouse.x = (double)mouse_screen.x;
	mouse.y = (double)mouse_screen.y;
	mouse.x = (mouse.x - SCREEN_WIDTH * 0.5) / SCREEN_WIDTH * 0.5;
	if (mouse.x < 0)
		mouse.x = -0.05235987756;
	else if (mouse.x == 0)
		return ;
	else
		mouse.x = 0.05235987756;
	if (plr->angle > 360)
		plr->angle = 0;
	else if (plr->angle < 0)
		plr->angle = 360;
	else
		plr->angle = plr->angle + mouse.x;
	/*plr->dir = vec2_rot(plr->dir, DEG_TO_RAD * mouse.x);*/
	transform_world_view(plr, home, mouse.x);
	SDL_WarpMouseInWindow(home->win.window, (int)(SCREEN_WIDTH * 0.5),
		(int)(SCREEN_HEIGHT * 0.5));
}

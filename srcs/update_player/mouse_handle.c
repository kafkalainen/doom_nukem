/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:55:46 by tmaarela          #+#    #+#             */
/*   Updated: 2021/03/02 11:06:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

float	mouse_acceleration(float mouse, char c)
{
	int		speed;
	if (c == 'x')
		speed = 100;
	else
		speed = 10000;
	if (mouse < 0)
		return (0.05235987756 * -mouse * speed);
	else if (mouse == 0)
		return (0);
	else
		return (-0.05235987756 * mouse * speed);

}

void	mouse_handle_win(t_player *plr, t_home *home, SDL_Event *e)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (e->type == SDL_MOUSEMOTION)
	{
		transform_world_view(home, -e->motion.xrel * DEG_TO_RAD);
		plr->pitch = MIN(MAX(plr->pitch - e->motion.yrel, 0), 480);
	}
}

void	mouse_handle_unix(t_player *plr, t_home *home)
{
	t_xy		mouse;
	t_screen_xy	mouse_screen;

	SDL_ShowCursor(SDL_DISABLE);
	SDL_CaptureMouse(SDL_TRUE);
	SDL_GetMouseState(&mouse_screen.x, &mouse_screen.y);
	mouse.x = (float)mouse_screen.x;
	mouse.y = (float)mouse_screen.y;
	mouse.x = (mouse.x - SCREEN_WIDTH * 0.5) / SCREEN_WIDTH * 0.5;
	mouse.y = (mouse.y - SCREEN_HEIGHT * 0.5) / SCREEN_HEIGHT * 0.5;
	transform_world_view(home, mouse_acceleration(mouse.x, 'x'));
	plr->pitch = MIN(MAX(plr->pitch + mouse_acceleration(mouse.y, 'y'), 0), 480);
	SDL_WarpMouseInWindow(home->win.window, (int)(SCREEN_WIDTH * 0.5),
		(int)(SCREEN_HEIGHT * 0.5));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:55:46 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/03 14:55:46 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h"

void	mouse_handle(t_player *plr, t_home *home)
{
	int x;
	int y;

	SDL_Event me;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//while (SDL_PollEvent(&me) != 0)
	{
		if (me.type == SDL_MOUSEMOTION)
		{
			plr->dir = vec2_rot(plr->dir, DEG_TO_RAD * me.motion.xrel);
		}
	}
}

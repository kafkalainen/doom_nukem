/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:55:46 by tmaarela          #+#    #+#             */
/*   Updated: 2021/03/19 14:28:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	mouse_handle(t_player *plr, t_home *home, SDL_Event *e)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (e->type == SDL_MOUSEMOTION)
	{
		// plr->dir.x += -e->motion.xrel * DEG_TO_RAD * 0.1;
		// plr->dir.y += -e->motion.xrel * DEG_TO_RAD * 0.1;
		// if (plr->dir.x > 2 * PI)
		// {
		// 	plr->dir.x = 0.0f;
		// 	plr->dir.y = 0.0f;
		// }
		// if (plr->dir.x < 0)
		// {
		// 	plr->dir.x = 2 * PI;
		// 	plr->dir.y = 2 * PI;
		// }
		transform_world_view(home, -e->motion.xrel * DEG_TO_RAD * 0.1);
		plr->pitch = ft_fmin(ft_fmax((plr->pitch - e->motion.yrel), 0), 480);
	}
}

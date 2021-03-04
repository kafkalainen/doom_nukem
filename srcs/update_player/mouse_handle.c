/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:55:46 by tmaarela          #+#    #+#             */
/*   Updated: 2021/03/04 16:06:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	mouse_handle(t_player *plr, t_home *home, SDL_Event *e)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (e->type == SDL_MOUSEMOTION)
	{
		transform_world_view(home, -e->motion.xrel * DEG_TO_RAD * 0.1);
		plr->pitch = ft_fmin(ft_fmax((plr->pitch - e->motion.yrel), 0), 480);
	}
}

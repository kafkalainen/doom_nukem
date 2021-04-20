/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:33:56 by tmaarela          #+#    #+#             */
/*   Updated: 2021/03/04 15:59:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	update_player(t_player *plr, t_home *home, SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0)
	{
		key_input(plr, e, home);
		mouse_handle(plr, home, e);
	}
	movement(plr, home);
}

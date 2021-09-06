/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:16:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 15:17:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	key_input(t_player *plr, SDL_Event *e, int *game_state)
{
	if (e->type == SDL_KEYDOWN)
		keys_down(plr, e->key.keysym.sym, game_state);
	else if (e->type == SDL_KEYUP)
		keys_up(plr, e->key.keysym.sym);
	else
		return ;
}

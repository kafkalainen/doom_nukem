/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:07:42 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/07 15:35:42 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	action_keys(t_player *plr, SDL_KeyCode *sym)
{
	if (*sym == K_Z && plr->input.wireframe == 1)
		plr->input.wireframe = 0;
	else if (*sym == K_Z && plr->input.wireframe == 0)
		plr->input.wireframe = 1;
	if (*sym == K_X && plr->input.minimap == 1)
		plr->input.minimap = 0;
	else if (*sym == K_X && plr->input.minimap == 0)
		plr->input.minimap = 1;
	if (*sym == K_C && plr->input.info == 1)
		plr->input.info = 0;
	else if (*sym == K_C && plr->input.info == 0)
		plr->input.info = 1;
	if (*sym == K_M && plr->input.mouse == 0)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		plr->input.mouse = 1;
	}
	else if (*sym == K_M && plr->input.mouse == 1)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		plr->input.mouse = 0;
	}
}

void	keys_down(t_player *plr, SDL_KeyCode sym, SDL_Event *e, int *game_state)
{
	if (sym == K_S)
		plr->input.down = 1;
	if (sym == K_W)
		plr->input.up = 1;
	if (sym == K_D)
		plr->input.right = 1;
	if (sym == K_A)
		plr->input.left = 1;
	if (sym == K_Q)
		plr->input.rot_left = 1;
	if (sym == K_E)
		plr->input.rot_right = 1;
	action_keys(plr, &sym);
}

void	keys_up(t_player *plr, SDL_KeyCode sym)
{
	if (sym == K_S)
		plr->input.down = 0;
	if (sym == K_W)
		plr->input.up = 0;
	if (sym == K_D)
		plr->input.right = 0;
	if (sym == K_A)
		plr->input.left = 0;
	if (sym == K_Q)
		plr->input.rot_left = 0;
	if (sym == K_E)
		plr->input.rot_right = 0;
}

void	key_input(t_player *plr, SDL_Event *e, int *game_state)
{
	if (e->type == SDL_KEYDOWN)
		keys_down(plr, e->key.keysym.sym, e, game_state);
	else if (e->type == SDL_KEYUP)
		keys_up(plr, e->key.keysym.sym);
	else
		return ;
}

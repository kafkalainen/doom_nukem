/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:07:42 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/11 16:05:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	action_keys(t_player *plr, SDL_KeyCode *sym)
{
	if (*sym == SDLK_z && plr->input.wireframe == 1)
		plr->input.wireframe = 0;
	else if (*sym == SDLK_z && plr->input.wireframe == 0)
		plr->input.wireframe = 1;
	if (*sym == SDLK_x && plr->input.minimap == 1)
		plr->input.minimap = 0;
	else if (*sym == SDLK_x && plr->input.minimap == 0)
		plr->input.minimap = 1;
	if (*sym == SDLK_c && plr->input.info == 1)
		plr->input.info = 0;
	else if (*sym == SDLK_c && plr->input.info == 0)
		plr->input.info = 1;
	if (*sym == SDLK_m && plr->input.mouse == 0)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		plr->input.mouse = 1;
	}
	else if (*sym == SDLK_m && plr->input.mouse == 1)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		plr->input.mouse = 0;
	}
}

static void	debug_keys(t_player *plr, SDL_KeyCode *sym, int nb)
{
	if (*sym == SDLK_UP)
		plr->input.debug_up = nb;
	if (*sym == SDLK_DOWN)
		plr->input.debug_down = nb;
	if (*sym == SDLK_LEFT)
		plr->input.debug_left = nb;
	if (*sym == SDLK_RIGHT)
		plr->input.debug_right = nb;
}

void	keys_down(t_player *plr, SDL_KeyCode sym, int *game_state)
{
	int	state;

	state = 1;
	if (sym == SDLK_ESCAPE)
		*game_state = MAIN_MENU;
	if (sym == SDLK_s)
		plr->input.down = 1;
	if (sym == SDLK_w)
		plr->input.up = 1;
	if (sym == SDLK_d)
		plr->input.right = 1;
	if (sym == SDLK_a)
		plr->input.left = 1;
	if (sym == SDLK_q)
		plr->input.rot_left = 1;
	if (sym == SDLK_e)
		plr->input.rot_right = 1;
	if (sym == SDLK_LCTRL)
		plr->input.crouch = 1;
	if (sym == SDLK_SPACE && plr->acceleration == 0)
		plr->acceleration = 5;
	debug_keys(plr, &sym, state);
	action_keys(plr, &sym);
}

void	keys_up(t_player *plr, SDL_KeyCode sym)
{
	int	state;

	state = 0;
	if (sym == SDLK_s)
		plr->input.down = 0;
	if (sym == SDLK_w)
		plr->input.up = 0;
	if (sym == SDLK_d)
		plr->input.right = 0;
	if (sym == SDLK_a)
		plr->input.left = 0;
	if (sym == SDLK_q)
		plr->input.rot_left = 0;
	if (sym == SDLK_e)
		plr->input.rot_right = 0;
	if (sym == SDLK_LCTRL)
		plr->input.crouch = 0;
	debug_keys(plr, &sym, state);
}

void	key_input(t_player *plr, SDL_Event *e, int *game_state)
{
	if (e->type == SDL_KEYDOWN)
		keys_down(plr, e->key.keysym.sym, game_state);
	else if (e->type == SDL_KEYUP)
		keys_up(plr, e->key.keysym.sym);
	else
		return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:07:42 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/03 12:48:08 by jnivala          ###   ########.fr       */
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

/*
**
**	Must change plr height standard to something to just assign default value,
**	Going to put it now to 6 and 3.
**	To create jump function, we need to make "gravity function", first.
**	Jumping creates a froce that gradually falls until you are at max height,
**	gravity pulling the player at all times
**	at a constant rate, lets say 0,2z per 10 frames.
**
*/

void	keys_down(t_player *plr, SDL_KeyCode sym, SDL_Event *e)
{
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
		plr->height = 3;
	if (sym == SDLK_SPACE && plr->acceleration == 0)
		plr->acceleration = 5;
	action_keys(plr, &sym);
	if (sym == SDLK_ESCAPE || e->type == SDL_QUIT)
		plr->input.quit = 1;
}

void	keys_up(t_player *plr, SDL_KeyCode sym)
{
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
		plr->height = 6;
}

void	key_input(t_player *plr, SDL_Event *e)
{
	if (e->type == SDL_KEYDOWN)
		keys_down(plr, e->key.keysym.sym, e);
	else if (e->type == SDL_KEYUP)
		keys_up(plr, e->key.keysym.sym);
	else
		return ;
}

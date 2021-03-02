/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:07:42 by tmaarela          #+#    #+#             */
/*   Updated: 2021/03/02 11:01:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		arrow_keys_down(t_player *plr, SDL_KeyCode sym)
{
	if (sym == k_s)
		plr->input.down = 1;
	if (sym == k_w)
		plr->input.up = 1;
	if (sym == k_d)
		plr->input.right = 1;
	if (sym == k_a)
		plr->input.left = 1;
}

void		arrow_keys_up(t_player *plr, SDL_KeyCode sym)
{
	if (sym == k_s)
		plr->input.down = 0;
	if (sym == k_w)
		plr->input.up = 0;
	if (sym == k_d)
		plr->input.right = 0;
	if (sym == k_a)
		plr->input.left = 0;
}

void		flight_keys_down(t_player *plr, SDL_KeyCode sym)
{
	if (sym == k_z)
		plr->input.z = 1;
	if (sym == k_x)
		plr->input.x = 1;
}

void		flight_keys_up(t_player *plr, SDL_KeyCode sym)
{
	if (sym == k_z)
		plr->input.z = 0;
	if (sym == k_x)
		plr->input.x = 0;
}

void		key_input(t_player *plr, SDL_Event *e, t_home *home)
{
	while(SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
		{
			cleanup_audio(&plr->audio);
			error_output_sdl("User closed the window", home);
		}
		else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == k_esc)
		{
			cleanup_audio(&plr->audio);
			error_output_sdl("User closed the window", home);
		}
		else if (e->type == SDL_KEYDOWN)
		{
			arrow_keys_down(plr, e->key.keysym.sym);
			flight_keys_down(plr, e->key.keysym.sym);
		}
		else if (e->type == SDL_KEYUP)
		{
			arrow_keys_up(plr, e->key.keysym.sym);
			flight_keys_up(plr, e->key.keysym.sym);
		}
	}
}

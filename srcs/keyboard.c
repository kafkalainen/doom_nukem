/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:07:42 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/18 16:07:42 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h"

void		key_input(t_player *plr, SDL_Event e, t_home *home)
{
	while(SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			ft_die("User closed the window", home);
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == k_esc)
			ft_die("User closed the window", home);
		// else if (e.type SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
		// 	position.z == "insert jump function";
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == k_up)
			plr->pos = vec2_add(plr->pos, vec2_mul(plr->dir, 4));
		// else if (e.type SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
		// 	position.y -= "insert movement rate backwards";
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == k_right)
			plr->dir = vec2_rot(plr->dir, 5 * DEG_TO_RAD);
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == k_left)
			plr->dir = vec2_rot(plr->dir, -5 * DEG_TO_RAD);
		// else if (e.type SDL_KEYDOWN && e.key.keysym.sym == SDLK_w)
		// 	position.y += "insert movement rate";
		// else if (e.type SDL_KEYDOWN && e.key.keysym.sym == SDLK_s)
		// 	position.y -= "insert movement rate backwards";
		// else if (e.type SDL_KEYDOWN && e.key.keysym.sym == SDLK_a)
		// 	position.x -= "insert strafe left ratio";
		// else if (e.type SDL_KEYDOWN && e.key.keysym.sym == SDLK_d)
		// 	position.x += "insert strafe right ratio";		
	}
}
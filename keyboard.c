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

#include "doom_nukem.h"

void		key_input(t_player *plr, SDL_Event e, t_home home)
{
	while(SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			ft_die("User closed the window", home);
		else if (e.type == SDLK_ESCAPE)
			ft_die("User closed the window", home);
		// else if (e.type == SDLK_SPACE)
		// 	position.z == "insert jump function";
		// else if (e.type == SDLK_UP)
		// 	position.y += "insert movement rate";
		// else if (e.type == SDLK_DOWN)
		// 	position.y -= "insert movement rate backwards";
		// else if (e.type == SDLK_LEFT)
		// 	position.x -= "insert strafe left ratio";
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == k_right)
			plr->pos.x += 1;
		// else if (e.type == SDLK_w)
		// 	position.y += "insert movement rate";
		// else if (e.type == SDLK_s)
		// 	position.y -= "insert movement rate backwards";
		// else if (e.type == SDLK_a)
		// 	position.x -= "insert strafe left ratio";
		// else if (e.type == SDLK_d)
		// 	position.x += "insert strafe right ratio";		
	}
}
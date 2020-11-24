/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:33:56 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/20 15:33:56 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h" 

void	init_player(t_player *plr, t_xy pos)
{
	plr->pos.x = pos.x;
	plr->pos.y = pos.y;
	plr->z = 0;
	plr->dir.x = 1;
	plr->dir.y = 0;
}

void	update_player(t_player *plr, t_home *home, SDL_Event e)
{
	key_input(plr, e, home);
	draw_rect_center(vec2(plr->pos.x, plr->pos.y), vec2(16, 16), home);
}

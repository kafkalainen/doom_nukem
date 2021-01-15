/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:33:56 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/15 12:07:49 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"
# ifdef __unix__
#  define MOUSE_HANDLE mouse_handle_unix
# elif defined(_WIN32) || defined(WIN32)
#  define MOUSE_HANDLE mouse_handle_win
# endif

void	update_player(t_player *plr, t_home *home, SDL_Event e, SDL_Surface *surf)
{
	key_input(plr, e, home);
	MOUSE_HANDLE(plr, home);
	movement(plr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:33:56 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/18 12:06:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"
# ifdef __unix__
#  define MOUSE_HANDLE mouse_handle_unix(plr, home)
# elif defined(_WIN32) || defined(WIN32)
#  define MOUSE_HANDLE mouse_handle_win(plr)
# endif

void	update_player(t_player *plr, t_home *home, SDL_Event e)
{
	key_input(plr, e, home);
	MOUSE_HANDLE;
	movement(plr);
}

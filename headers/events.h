/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:09 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/07 12:51:44 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

/*
** Event handlers
*/

void			key_input(t_player *plr, SDL_Event *e, int *game_state);
void			mouse_handle(t_player *plr, SDL_Event *e);

#endif

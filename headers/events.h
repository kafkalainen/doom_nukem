/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:09 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/03 15:33:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

/*
** Event handlers
*/

void			key_input(t_player *plr, SDL_Event *e, int *game_state);
void			keys_down(t_player *plr, SDL_KeyCode sym, int *game_state);
void			keys_up(t_player *plr, SDL_KeyCode sym);
void			mouse_handle(t_player *plr, SDL_Event *e);

#endif

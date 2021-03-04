/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:09 by tmaarela          #+#    #+#             */
/*   Updated: 2021/03/04 16:00:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

/*
** Event handlers
*/

void			key_input(t_player *plr, SDL_Event *e, t_home *home);
void			mouse_handle(t_player *plr, t_home *home, SDL_Event *e);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:57 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/20 19:50:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_FUNCTIONS_H
# define PLAYER_FUNCTIONS_H

/*
** Player functions
*/

void			init_player(t_player *plr);
void			update_player(t_player *plr, t_home *home, SDL_Event *e);
void			movement(t_player *plr, t_home *home);
void			player_move_forward(t_player *plr, t_home *home, float delta_time);
void			player_move_strafe(t_player *plr, t_home *home, float delta_time, char ad);
void			player_move_backwards(t_player *plr, t_home *home, float delta_time);
int				plr_inside(t_sector *sector, t_xy *pos);

#endif

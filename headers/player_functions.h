/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:57 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/22 14:06:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_FUNCTIONS_H
# define PLAYER_FUNCTIONS_H

void		calc_intersection(t_polygon *pgon, t_polygon *first, t_player *plr,
					t_intersection *sect);
t_xy		line_intersection(t_intersection *sect);

/*
** Player functions
*/

void			init_player(t_player *plr);
void			update_player(t_player *plr, t_home *home, SDL_Event e);
void			movement(t_player *plr);
void			player_move_forward(t_player *plr, float delta_time);
void			player_move_strafe(t_player *plr, float delta_time, char ad);
void			player_move_backwards(t_player *plr, float delta_time);

#endif

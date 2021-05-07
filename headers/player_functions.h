/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:57 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/07 11:37:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_FUNCTIONS_H
# define PLAYER_FUNCTIONS_H

/*
** Player functions
*/

int		check_height_diff(t_xy *dir, float *z, t_point *to, t_point *behind);
void	init_player(t_player *plr);
int		player_move(t_player *plr, t_home *home, t_xy *dir);
int		plr_inside(t_sector *sector, t_xy *pos);
void	update_player(t_player *plr, t_home *home, SDL_Event *e);
void	update_height(t_xy *dir, float *z, t_point *to, int walls);

#endif

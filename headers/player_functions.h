/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:57 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/06 15:56:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_FUNCTIONS_H
# define PLAYER_FUNCTIONS_H

/*
** Player functions
*/

void	init_player(t_player *plr);
void	update_player(t_player *plr, t_home *home, SDL_Event *e);
int		plr_inside(t_sector *sector, t_xy *pos);
int		player_move(t_player *plr, t_home *home, t_xy *dir);
int		check_height_diff(t_xy *dir, float *z, t_point *to);


#endif

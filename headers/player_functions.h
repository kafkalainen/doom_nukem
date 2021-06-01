/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:57 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/01 08:36:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_FUNCTIONS_H
# define PLAYER_FUNCTIONS_H

/*
** Player functions
*/

int		check_height_diff(t_xy *dir, float *z, t_wall *to, t_wall *behind);
void	init_player(t_player *plr);
int		player_move(t_player *plr, t_home *home, t_xy *dir);
int		plr_inside(t_sector *sector, t_xy *pos);
void	update_player(t_player *plr, t_home *home, SDL_Event *e);
void	update_height(t_xy *dir, float *z, t_wall *to, int walls);
void	create_target_vector(t_player *plr);
#endif

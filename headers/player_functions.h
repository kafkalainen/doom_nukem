/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:57 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/11 16:23:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_FUNCTIONS_H
# define PLAYER_FUNCTIONS_H

/*
** Player functions
*/

t_xyz	check_y(t_sector *sector, t_xyz pos, float cur_height);
int		check_y_diff(t_xyz *current_pos, t_xyz *test_pos, t_sector *to,
	float cur_height);
void	crouch(t_player *plr, Uint32 delta_time);
void	init_player(t_player *plr);
int		player_move(t_player *plr, t_home *home, Uint32 delta_time);
int		plr_inside(t_sector *sector, t_xy *pos);
void	update_player(t_player *plr, t_home *home, Uint32 delta_time);
void	update_height(t_xy *dir, float *z, t_wall *to, int walls);
void	create_target_vector(t_player *plr);
#endif

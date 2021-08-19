/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:12:34 by tmaarela          #+#    #+#             */
/*   Updated: 2021/08/19 14:58:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	shooting_handle(t_home *home, t_player *plr)
{
	if (home->projectile_idx >= MAX_PROJECTILES - 1)
		home->projectile_idx = -1;
	if (home->nbr_of_projectiles < MAX_PROJECTILES)
		home->nbr_of_projectiles++;
	home->projectile_idx++;
	get_bullet_ricochet_hit_point(home, plr, plr->cur_sector);
}

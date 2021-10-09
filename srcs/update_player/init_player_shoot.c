/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_shoot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:42:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/09 13:57:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	init_player_shoot(t_ray *ray, t_xyz pos, t_xyz dir, int sector)
{
	ray->dir = dir;
	ray->end_sector = -1;
	ray->plr_pos = pos;
	ray->pos = pos;
	ray->side = 0;
	ray->start_sector = sector;
	return (PLAYER);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enemy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:50:47 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 09:58:40 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	is_enemy(int type)
{
	if (type == skull_skulker || type == thing
		|| type == drone || type == crewmember)
		return (true);
	return (false);
}

t_bool	is_enemy_sprite(int type)
{
	if (type == -enemy0 || type == -enemy1
		|| type == -enemy2 || type == -enemy3)
		return (true);
	return (false);
}

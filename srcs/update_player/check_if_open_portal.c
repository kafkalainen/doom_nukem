/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_open_portal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 11:50:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 13:26:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_if_open_portal(t_wall *wall)
{
	if ((wall->top.type >= 0 && !wall->is_door && !wall->is_window)
		|| (wall->is_door && !wall->is_closed && wall->is_locked == unlocked))
	{
		return (true);
	}
	return (false);
}

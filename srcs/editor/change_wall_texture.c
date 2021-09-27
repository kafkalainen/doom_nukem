/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:31:05 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/27 14:33:21 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	change_normal_wall_texture(int *wall_type)
{
	if (*wall_type == -wall0)
		*wall_type = -wall1;
	else if (*wall_type == -wall1)
		*wall_type = -wall2;
	else if (*wall_type == -wall2)
		*wall_type = -wall3;
	else if (*wall_type == -wall3)
		*wall_type = -wall4;
	else if (*wall_type == -wall4)
		*wall_type = -small_window;
	else if (*wall_type == -small_window)
		*wall_type = -large_window;
	else if (*wall_type == -large_window)
		*wall_type = -wall7;
	else if (*wall_type == -wall7)
		*wall_type = -wall8;
	else if (*wall_type == -wall8)
		*wall_type = -wall9;
	else if (*wall_type == -wall9)
		*wall_type = -wall0;
	return (false);
}

t_bool	change_wall_texture(int	*wall_type, t_action *action)
{
	if (*wall_type < 0)
		action->change_wall_texture = change_normal_wall_texture(wall_type);
	return (false);
}

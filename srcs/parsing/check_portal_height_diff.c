/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_portal_height_diff.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 08:24:45 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/22 16:35:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	check_portal_floor_difference(t_wall *portal,
	t_wall *portal_behind, t_bool *validation)
{
	if (portal->bottom.p[0].y > portal_behind->bottom.p[2].y)
		*validation = true;
	else if (portal->bottom.p[2].y > portal_behind->bottom.p[0].y)
		*validation = true;
	else
		*validation = false;
}

void	check_portal_ceiling_difference(t_wall *portal,
	t_wall *portal_behind, t_bool *validation)
{
	if (portal->top.p[1].y < portal_behind->top.p[2].y)
		*validation = true;
	else if (portal->top.p[2].y < portal_behind->top.p[1].y)
		*validation = true;
	else
		*validation = false;
}

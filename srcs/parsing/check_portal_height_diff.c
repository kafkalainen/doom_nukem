/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_portal_height_diff.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 08:24:45 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/10 14:16:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	check_portal_floor_difference(t_wall *portal,
	t_wall *portal_behind)
{
	if (portal->bottom.p[0].y > portal_behind->bottom.p[2].y)
		return (1);
	else if (portal->bottom.p[2].y > portal_behind->bottom.p[0].y)
		return (1);
	else
		return (0);
}

Uint32	check_portal_ceiling_difference(t_wall *portal,
	t_wall *portal_behind)
{
	if (portal->top.p[1].y < portal_behind->top.p[2].y)
		return (1);
	else if (portal->top.p[2].y < portal_behind->top.p[1].y)
		return (1);
	else
		return (0);
}

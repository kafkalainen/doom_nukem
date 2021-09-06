/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_same_point.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:50:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/26 17:52:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	check_if_same_point(t_xyz a, t_xyz b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w)
		return (TRUE);
	else
		return (FALSE);
}

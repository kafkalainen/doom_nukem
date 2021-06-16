/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_door_to_portal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:35:38 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/16 15:41:30 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	change_door_to_portal(int door)
{
	if (door >= DOOR_INDEX)
		return (door - DOOR_INDEX);
	else
		return (door);
}

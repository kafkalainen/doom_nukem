/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_door_to_portal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:35:38 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 10:31:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	change_door_to_portal(int door)
{
	if (door >= DOOR_INDEX && door < CLEANING_INDEX)
		return (door - DOOR_INDEX);
	else if (door >= CLEANING_INDEX && door < ENGINEERING_INDEX)
		return (door - CLEANING_INDEX);
	else if (door >= ENGINEERING_INDEX && door < MILITARY_INDEX)
		return (door - ENGINEERING_INDEX);
	else if (door >= MILITARY_INDEX && door < SECRET_INDEX)
		return (door - MILITARY_INDEX);
	else if (door >= SECRET_INDEX && door < SMALL_WINDOW_INDEX)
		return (door - SECRET_INDEX);
	else if (door >= SMALL_WINDOW_INDEX && door < LARGE_WINDOW_INDEX)
		return (door - SMALL_WINDOW_INDEX);
	else if (door >= LARGE_WINDOW_INDEX)
		return (door - LARGE_WINDOW_INDEX);
	else
		return (door);
}

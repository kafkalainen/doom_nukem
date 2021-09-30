/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entity_difficulty.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:43:25 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/30 15:43:50 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	set_entity_health(t_uint type, float difficulty)
{
	if (type == skull_skulker || type == drone)
	{
		if (difficulty == EASY)
			return (1);
		if (difficulty == NORMAL)
			return (2);
		if (difficulty == HARD)
			return (4);
	}
	else if (type == crewmember || type == thing)
	{
		if (difficulty == EASY)
			return (2);
		if (difficulty == NORMAL)
			return (3);
		if (difficulty == HARD)
			return (6);
	}
	return (1);
}

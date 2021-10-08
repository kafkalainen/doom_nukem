/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recharge_suit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:58:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 10:26:57 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	recharge_suit(t_player *plr, Uint32 t)
{
	if (plr->recharge > 0)
	{
		plr->recharge -= t;
		if (plr->recharge <= 0)
		{
			if (plr->power_points < 8)
				plr->power_points += 4;
			if (plr->power_points > 8)
				plr->power_points = 8;
		}
	}
}

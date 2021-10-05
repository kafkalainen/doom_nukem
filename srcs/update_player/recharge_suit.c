/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recharge_suit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:58:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/05 14:02:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	recharge_suit(t_player *plr, Uint32 t)
{
	if (plr->recharge)
	{
		plr->recharge -= t;
		if (plr->recharge <= t)
		{
			if (plr->power_points < 5)
				plr->power_points += 3;
			if (plr->power_points > 5)
				plr->power_points = 5;
		}
	}
}

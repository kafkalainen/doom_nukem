/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:02:45 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/11 16:17:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	crouch(t_player *plr, Uint32 delta_time)
{
	static Uint32 animation_duration = 300;

	if (plr->input.crouch)
	{
		if (animation_duration)
		{
			animation_duration -= delta_time;
			plr->height -= 0.01f;
			if (plr->height <= 0.6f)
				plr->height = 0.6f;
		}
	}
	// else
	// {
	// 	animation_duration += delta_time;
	// 	plr->height += 0.01f;
	// 	if (plr->height > 1.5f)
	// 		plr->height = 1.5f;
	// }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:27:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/27 11:28:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	mouse_zoom(t_action *action, int zoom)
{
	if (zoom)
	{
		action->scalarf *= 2.0f;
		action->offsetf.x -= action->world_pos.x;
		action->offsetf.y += action->world_pos.y;
		action->offsetf.x *= action->scalarf;
		action->offsetf.y *= action->scalarf;
	}
	else
	{
		action->scalarf *= 0.5f;
		action->offsetf.x -= action->world_pos.x * action->scalarf;
		action->offsetf.y += action->world_pos.y * action->scalarf;
		action->offsetf.x *= action->scalarf;
		action->offsetf.y *= action->scalarf;
	}
}

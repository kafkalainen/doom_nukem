/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_story.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:59:56 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/12 11:30:49 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	free_story(char ***array)
{
	Uint32 i;

	i = STORY_STRINGS;
	while (i--)
	{
		free(*(*array + i));
		*(*array + i) = NULL;
	}
	free(*array);
	*array = NULL;
}

Uint32	evolve_story(t_player *plr)
{
	if (plr->plot_state != cutscene2)
	{
		plr->plot_state++;
		plr->message_time = plr->time + 10000;
		return (TRUE);
	}
	else
		return (FALSE);
}

void	draw_plot_state(char **array, Uint32 state, Uint32 *buffer, t_player *plr)
{
	t_plx_modifier	mod;

	if (plr->message_time > plr->time)
	{
		mod.colour = get_color(white);
		mod.size = TEXT_SIZE;
		mod.len = ft_strlen(array[state]);
		ft_str_pxl(buffer, (t_xy){100, SCREEN_HEIGHT - 30}, array[state], mod);
	}
}

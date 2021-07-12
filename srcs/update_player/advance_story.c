/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_story.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:59:56 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/12 13:42:04 by jnivala          ###   ########.fr       */
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
	float			percentage;

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	if (plr->message_time > plr->time + 3000)
	{
		percentage = 1.0f - ((plr->message_time - plr->time) * 0.00007f);
		mod.len = (size_t)(ft_strlen(array[state]) * percentage);
		ft_str_pxl(buffer, (t_xy){100, SCREEN_HEIGHT - 30}, array[state], mod);
	}
	else if (plr->message_time > plr->time)
	{
		mod.len = (size_t)(ft_strlen(array[state]));
		ft_str_pxl(buffer, (t_xy){100, SCREEN_HEIGHT - 30}, array[state], mod);
	}
}

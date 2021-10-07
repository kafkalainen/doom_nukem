/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:25:29 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/07 13:14:15 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	check_button_events(t_button *button, t_action *action, int i)
{
	if (button->info.draw_depth == depth_zero)
		main_button_actions(action, i);
	else if (button->info.draw_depth == sector)
		sector_button_actions(action, i);
	else if (button->info.draw_depth == entity)
		entity_button_actions(action, i);
	else if (button->info.draw_depth == wall)
		wall_button_actions(action, i);
}

void	check_ui_events(int x, int y, t_button ***blist, t_action *action)
{
	t_button	**list;
	int			i;
	t_xy		click_ui;

	i = 0;
	list = *blist;
	click_ui = vec2(x, y);
	while (i < NBR_BUTTONS)
	{
		if (list[i]->info.draw_depth == action->draw_depth)
		{
			if (check_bbox_ui(list[i]->box.start, list[i]->box.end, click_ui)
				&& list[i]->is_active)
			{
				check_button_events(list[i], action, i);
				break ;
			}
		}
		i++;
	}
	if (i == NBR_BUTTONS)
		reset_actions(action);
}

t_bool	clicked_inside_grid(int x, int y, int height, int width)
{
	if (x > 300 && x < width && y > 0 && y < height)
		return (true);
	return (false);
}

t_bool	clicked_inside_ui(int x, int y, int height, int width)
{
	if (x > 0 && x < 300 && x < width && y > 0 && y < height)
		return (true);
	return (false);
}

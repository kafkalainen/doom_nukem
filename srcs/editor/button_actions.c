/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:11:16 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/08 18:01:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void		main_button_actions(t_action *action, int i)
{
	if (i == 0)
	{
		action->save_file = 1;
		if (!action->map_name_set)
			action->input_active = 1;
	}
	else if (i == 1 && action->nbr_of_maps > 0)
		action->open_file = 1;
	else if (i == 2)
	{
		if (action->grid)
			action->grid = 0;
		else
			action->grid = 1;
	}
	else if (i == 3)
	{
		if (!action->create_sector)
			action->create_sector = 1;
	}
	else if (i == 4)
		action->assign_end_sector = 1;
	else if (i == 5  && action->nbr_of_maps > 0)
		action->link_maps = 1;
	else if (i == 6)
		action->unlink_maps = 1;
	else if (i == 7)
		action->assign_player_start = 1;
	else if (i == 8)
		action->create_elevator = 1;
}

void	entity_button_actions(t_action *action, int i)
{
	action->edit_entity = 1;
	if (i == 25)
		action->change_entity_type = 1;
	else if (i == 26)
		action->toggle_entity_is_linked = 1;
	else if (i == 27)
		action->toggle_is_revealed = 1;
	else if (i == 28)
		action->toggle_is_static = 1;
	else if (i == 29)
		action->toggle_state = 1;
}

void	sector_button_actions(t_action *action, int i)
{
	// 10 - 15
	action->edit_sector = 1;
	if (i == 10)
		action->change_floor_texture = 1;
	else if (i == 11)
		action->change_ceiling_texture = 1;
	else if (i == 12)
		action->set_light_intensity = 1;
	else if (i == 14)
		action->create_light_source = 1;
	else if (i == 15)
		action->input_active = 1;
	else if (i == 16)
		action->add_wall_point = 1;
}

void	wall_button_actions(t_action *action, int i)
{
	action->edit_wall = 1;
	if (i == 18) // wall texture
		action->change_wall_texture = 1;
	else if (i == 19) // convert to portal
		action->convert_to_portal = 1;
	else if (i == 20) // ceiling height
	{
		printf("edit walls ceiling height\n");
		action->edit_ceiling_height = 1;
		action->input_active = 1;
	}
	else if (i == 21) // floor height
	{
		printf("edit walls floor height\n");
		action->edit_floor_height = 1;
		action->input_active = 1;
	}

	else if (i == 22) // light button
	{
		action->create_light_button = 1;
		printf("add a light button\n");
	}

	else if (i == 23) // powerstation
	{
		action->create_powerstation = 1;
		printf("add a powerstation\n");
	}

}

int		check_bbox(t_xy start, t_xy end, int mouse_x, int mouse_y)
{
	if (start.x <= mouse_x && start.y <= mouse_y &&
		end.x >= mouse_x && end.y >= mouse_y)
		return (TRUE);
	else
		return (FALSE);
}

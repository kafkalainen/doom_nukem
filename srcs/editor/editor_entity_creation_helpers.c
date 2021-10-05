/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_entity_creation_helpers.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:31:05 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/05 14:57:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	init_static_shared_vals(t_entity_list *new, int sector_idx)
{
	new->is_active = true;
	new->is_linked = 0;
	new->is_revealed = false;
	new->is_static = true;
	new->state = true;
	new->sector_idx = sector_idx;
}

static void	init_lamp_pos_dir(t_entity_list *new,
	t_editor_sector *sector, t_xy pos)
{
	new->pos.x = ft_roundf_to_grid(pos.x, 0);
	new->pos.z = ft_roundf_to_grid(pos.y, 0);
	new->pos.y = get_lowest_ceiling_height(&sector->walls,
			sector->nb_of_walls);
	new->dir.x = 0;
	new->dir.y = -1;
	new->dir.z = 0;
}

void	init_static_entity(t_entity_list *new, t_action *action,
	t_editor_sector *sector, t_xy pos)
{
	if (action->create_elev_button)
		new->type = lift_button;
	else if (action->create_light_button)
		new->type = light_button;
	else if (action->create_powerstation)
		new->type = powerstation;
	else
		new->type = lamp;
	init_static_shared_vals(new, sector->idx_sector);
	if (action->create_elev_button || action->create_light_button
		|| action->create_powerstation)
	{
		get_midpoint_of_walls(sector, action->selected_wall,
			&new->pos.x, &new->pos.z);
		new->pos.y = get_selected_floor_height(sector,
				action->selected_wall) + 1;
		get_direction_from_wall(new, sector, action->selected_wall);
	}
	else if (new->type == lamp)
		init_lamp_pos_dir(new, sector, pos);
}

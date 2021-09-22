/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_entity_creation_is_allowed.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:43:46 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/22 09:57:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	calc_entities_in_sector_with_type(t_entity_list **head,
	int sector_idx, int entity_type)
{
	t_entity_list	*temp;
	int				count;

	count = 0;
	temp = *head;
	while (temp != NULL)
	{
		if (temp->entity_type == entity_type
			&& temp->sector_idx == sector_idx)
			count++;
		temp = temp->next;
	}
	return (count);
}

t_bool	check_non_static_entities_for_overlap(t_entity_list **head,
	t_editor_sector *sector, t_xy pos)
{
	t_entity_list	*temp;
	t_editor_walls	*wall;
	int				i;
	t_screen_xy		x0;

	x0.x = ft_roundf_to_grid(pos.x, 0);
	x0.y = ft_roundf_to_grid(pos.y, 0);
	temp = *head;
	while (temp != NULL)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, vec2(x0.x, x0.y)))
			return (false);
		temp = temp->next;
	}
	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (wall->x0.x == x0.x && wall->x0.y == x0.y)
			return (false);
		wall = wall->next;
		i++;
	}
	return (true);
}

t_bool	check_static_entities_for_overlap(t_entity_list **head,
	t_editor_sector *sector, int wall_idx, int light_boolean)
{
	t_entity_list	*temp;
	t_screen_xy		x0;

	x0.x = 0;
	x0.y = 0;
	if (!light_boolean)
		get_midpoint_of_walls(sector, wall_idx, &x0.x, &x0.y);
	else
	{
		x0.x = sector->centroid.x;
		x0.y = sector->centroid.y;
	}
	temp = *head;
	while (temp != NULL)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, vec2(x0.x, x0.y)))
			return (false);
		temp = temp->next;
	}
	return (true);
}

static	t_bool	entity_creation_is_allowed_two(t_entity_list **head,
		t_editor_sector *sector, t_action *action)
{
	if (action->create_light_button || action->create_powerstation
		|| action->create_elev_button || action->create_light_source)
		if (!check_static_entities_for_overlap(head, sector,
				action->selected_wall, action->create_light_source))
			return (false);
	if (action->create_entity)
		if (!check_non_static_entities_for_overlap(head,
				sector, action->world_pos))
			return (false);
	if (action->create_light_button
		&& calc_entities_in_sector_with_type(head, sector->idx_sector,
			light_button))
		return (false);
	if (action->create_light_source
		&& calc_entities_in_sector_with_type(head, sector->idx_sector,
			lamp))
		return (false);
	if (action->create_elev_button
		&& calc_entities_in_sector_with_type(head, sector->idx_sector,
			lift_button))
		return (false);
	return (true);
}

t_bool	entity_creation_is_allowed(t_entity_list **head,
		t_editor_sector *sector, t_action *action)
{
	int				i;
	t_editor_walls	*wall;

	if (!sector)
		return (false);
	wall = sector->walls;
	i = 0;
	while (i < sector->nb_of_walls)
	{
		if (action->selected_wall == wall->idx && wall->type >= 0)
			return (false);
		wall = wall->next;
		i++;
	}
	return (entity_creation_is_allowed_two(head, sector, action));
}

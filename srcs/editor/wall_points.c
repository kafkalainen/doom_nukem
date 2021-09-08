/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:40:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/07 16:43:47 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	close_editor_wall_list(t_editor_walls **head)
{
	t_editor_walls	*temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = *head;
}

int	check_for_last_point(t_sector_list *sector, t_mouse_data *data,
	t_action *action)
{
	t_xy		mouse;
	double 		dist;

	mouse.x = (data->x - action->offset.x) / action->scalar;
	mouse.y = (data->y - action->offset.y) / action->scalar;

	dist = sqrt(pow(fabs(sector->walls->x0.x - mouse.x), 2.0f) +
		pow(fabs(sector->walls->x0.y - mouse.y), 2.0f));

	if (!sector->walls)
		return (0);
	if (dist <= 1)
		return (1);
	return (0);
}

void	remove_last_point(t_editor_walls **walls, int *nb_of_walls,
		int selected_point)
{
	t_editor_walls	*previous;
	t_editor_walls	*deleted;
	int				i;

	i = 0;
	previous = *walls;
	while(previous != NULL && i++ < selected_point - 1)
		previous = previous->next;
	deleted = previous->next;
	if (deleted == NULL)
		return ;
	free(deleted);
	deleted = NULL;
	previous->next = NULL;
	*nb_of_walls -= 1;
	return ;
}

static int	bake_last_point(t_sector_list *sector, t_action *action,
			t_editor_walls *point)
{
	point = sector->walls;
	while (point && point->next)
		point = point->next;
	if (check_for_intersecting_lines(sector, point->x0, sector->walls->x0))
		ft_putendl("ERROR: Cannot close sector, lines intersecting.");
	else
	{
		close_editor_wall_list(&sector->walls);
		if (check_if_non_convex(sector))
		{
			ft_putendl("ERROR: Non-convex sector.");
			return (3);
		}
		action->selected_sector = sector->idx_sector;
		assign_sector_bbox(sector);
		action->edit_sector = 0;
	}
	return (0);
}

int	add_point_to_list(t_sector_list *sector, t_mouse_data *data,
	t_action *action)
{
	t_editor_walls	*point;
	t_screen_xy		coord;

	coord.x = (data->x - action->offset.x) / action->scalar;
	coord.y = (data->y - action->offset.y) / action->scalar;
	if (sector == NULL)
		return (1);
	if (sector->nb_of_walls > 1 && check_for_last_point(sector, data, action))
		return(bake_last_point(sector, action, point));
	point = sector->walls;
	while (point && point->next)
		point = point->next;
	if (point && check_for_intersecting_lines(sector, point->x0, coord))
		ft_putendl("ERROR: Cannot put down the point, intersecting with other lines.");
	else
	{
		point = new_wall_point(data, action);
		if (point)
			add_point_end(&sector->walls, point);
		else
			error_output("Error while allocating wallpoints.");
		sector->nb_of_walls += 1;
		action->selected_point +=1;
	}
	return (0);
}

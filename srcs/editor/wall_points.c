/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:40:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 15:09:04 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void		assign_sector_bbox(t_sector_list *sector)
{
	t_screen_xy		min;
	t_screen_xy		max;
	t_editor_walls	*temp;
	int				i;

	i = 0;
	min = (t_screen_xy){9001, 9001};
	max = (t_screen_xy){-9001, -9001};
	temp = sector->walls;
	while (i < sector->nb_of_walls && temp != NULL)
	{
		if (min.x > temp->x0.x)
			min.x = temp->x0.x;
		if (min.y > temp->x0.y)
			min.y = temp->x0.y;
		if (max.x < temp->x0.x)
			max.x = temp->x0.x;
		if (max.y < temp->x0.y)
			max.y = temp->x0.y;
		temp = temp->next;
		i++;
	}
	sector->bbox.start.x = min.x;
	sector->bbox.start.y = min.y;
	sector->bbox.end.x = max.x;
	sector->bbox.end.y = max.y;
	sector->bbox.start.w = 1.0f;
	sector->bbox.end.w = 1.0f;
}

t_editor_walls	*new_wall_point(t_mouse_data *data, t_action *action)
{
	t_editor_walls	*new;

	new = (t_editor_walls *)malloc(sizeof(*new));
	if (new != NULL)
	{
		new->x0.x = (data->x - action->offset.x) / action->scalar; // casting mouse data to int makes the grid be offset by 3-4 units
		new->x0.y = (data->y - action->offset.y) / action->scalar; // without it there is no snapping on walls on windows
		new->idx = -1;
		new->type = 0;
		new->bbox.start = vec2(new->x0.x - 1, new->x0.y - 1);
		new->bbox.end = vec2((new->x0.x + 1), (new->x0.y + 1));
		new->height.ground = 0;
		new->height.ceiling = 3;
		new->next = NULL;
	}
	else
	{
		free(new);
		new = NULL;
	}
	return (new);
}

void	add_point_end(t_editor_walls **point, t_editor_walls *new)
{
	t_editor_walls	*temp;
	int				i;

	i = 0;
	if (new == NULL)
		return ;
	if (*point == NULL)
	{
		new->idx = i;
		*point = new;
	}
	else
	{
		temp = *point;
		while (temp->next != NULL)
		{
			i++;
			temp = temp->next;
		}
		i++;
		new->idx = i;
		temp->next = new;
		new->next = NULL;
	}
}

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
	printf("moved to the end temp-idx is %d\n", selected_point);
	if (deleted == NULL)
		return ;
	printf("moved to point is x %d and y %d\n", deleted->x0.x, deleted->x0.y);
	printf("freeing wallpoint\n");
	free(deleted);
	deleted = NULL;
	previous->next = NULL;
	*nb_of_walls -= 1;
	return ;
}

/* void	move_sector_bbox(t_sector_list *sector);
{

} */

/* int	lseg_wall(t_sector_list *sector, t_mouse_data *data)
{
	t_editor_walls *point_0;

	point_0 = sector->walls;
}
 */

int	add_point_to_list(t_sector_list *sector, t_mouse_data *data,
	t_action *action)
{
	t_editor_walls	*point;
	t_screen_xy		coord;

	coord.x = (data->x - action->offset.x) / action->scalar;
	coord.y = (data->y - action->offset.y) / action->scalar;
	if (sector == NULL)
		return (1);
	if (sector->nb_of_walls > 1)
		if (check_for_last_point(sector, data, action))
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

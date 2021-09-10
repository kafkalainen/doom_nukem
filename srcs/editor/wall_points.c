/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:40:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/10 16:19:32 by jnivala          ###   ########.fr       */
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

int	check_for_last_point(t_editor_sector *sector, t_action *action)
{
	t_xy		mouse;
	double		dist;

	mouse = vec2(action->world_pos.x, action->world_pos.y);
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

static int	add_last_point(t_editor_sector **head, t_editor_sector *sector,
			t_action *action, t_editor_walls *point)
{
	point = sector->walls;
	while (point && point->next)
		point = point->next;
	if (check_all_sectors_for_intersecting_lines(head, point->x0, sector->walls->x0))
		ft_putendl("ERROR: Cannot close sector, lines intersecting.");
	else
	{
		close_editor_wall_list(&sector->walls);
		action->selected_sector = sector->idx_sector;
		if (check_if_non_convex(sector))
		{
			ft_putendl("ERROR: Non-convex sector.");
			return (3);
		}
		assign_sector_bbox(sector);
		if (check_if_another_sector_is_inside(sector, head))
		{
			ft_putendl("ERROR: Another sector inside");
			return (3);
		}
		sector->centroid = calculate_centroid(sector);
		editor_sort_wall_vertices(sector);
		action->create_sector = idle;
	}
	return (0);
}

float	ft_roundf_to_grid(float nb, int prec)
{
	long double	fraction;

	if (prec < 0)
		return (nb);
	fraction = 0.5;
	while (prec)
	{
		fraction = fraction * 0.1;
		prec--;
	}
	if (nb > 0)
		nb += fraction;
	else
		nb -= fraction;
	return (nb);
}

int	add_point_to_list(t_editor_sector **head, t_editor_sector *sector, t_action *action)
{
	t_editor_walls	*point;
	t_screen_xy		new_coord;

	point = NULL;
	new_coord = round_coordinates(action->world_pos);
	if (sector == NULL)
		return (1);
	if (sector->nb_of_walls > 1 && check_for_last_point(sector, action))
		return (add_last_point(head, sector, action, point));
	point = sector->walls;
	while (point && point->next)
		point = point->next;
	if (point && check_all_sectors_for_intersecting_lines(head, point->x0, new_coord))
		ft_putendl("ERROR: Cannot put down the point, intersecting with other lines.");
	else
	{
		point = new_wall_point(new_coord);
		if (point)
			add_point_end(&sector->walls, point);
		else
			error_output("Error while allocating wallpoints.");
		sector->nb_of_walls += 1;
		action->selected_point +=1;
	}
	return (0);
}

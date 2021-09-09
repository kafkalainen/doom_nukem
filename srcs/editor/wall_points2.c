/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_points2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:05:47 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/09 09:31:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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
	sector->bbox.start.y = max.y;
	sector->bbox.end.x = max.x;
	sector->bbox.end.y = min.y;
}

t_editor_walls	*new_wall_point(t_screen_xy world_coord)
{
	t_editor_walls	*new;

	new = (t_editor_walls *)malloc(sizeof(*new));
	if (new != NULL)
	{
		new->x0.x = world_coord.x;
		new->x0.y = world_coord.y;
		new->idx = -1;
		new->type = 0;
		new->bbox.start = vec2(new->x0.x - 0.2f, new->x0.y + 0.2f);
		new->bbox.end = vec2((new->x0.x + 0.2f), (new->x0.y - 0.2f));
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

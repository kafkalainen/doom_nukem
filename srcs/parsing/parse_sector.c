/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:31:08 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/21 10:47:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_wall	*new_point(t_point_data *left, t_point_data *right)
{
	t_wall	*wall;

	wall = (t_wall *)malloc(sizeof(*wall));
	if (wall != NULL)
	{
		wall->top.p[0] = (t_xyz){left->x, left->ground, left->y, 1.0f};
		wall->top.p[1] = (t_xyz){left->x, left->ceiling, left->y, 1.0f};
		wall->top.p[2] = (t_xyz){right->x, right->ceiling, right->y, 1.0f};
		wall->top.uv[0] = (t_uvz){0.0f, 1.0f, 1.0f};
		wall->top.uv[1] = (t_uvz){0.0f, 0.0f, 1.0f};
		wall->top.uv[2] = (t_uvz){1.0f, 0.0f, 1.0f};
		wall->bottom.p[0] = (t_xyz){left->x, left->ground, left->y, 1.0f};
		wall->bottom.p[1] = (t_xyz){right->x, right->ceiling, right->y, 1.0f};
		wall->bottom.p[2] = (t_xyz){right->x, right->ground, right->y, 1.0f};
		wall->bottom.uv[0] = (t_uvz){0.0f, 1.0f, 1.0f};
		wall->bottom.uv[1] = (t_uvz){1.0f, 0.0f, 1.0f};
		wall->bottom.uv[2] = (t_uvz){1.0f, 1.0f, 1.0f};
		wall->top.idx = change_door_to_portal(left->idx);
		wall->bottom.idx = change_door_to_portal(left->idx);
		wall->is_closed = 0;
		wall->open_until = 0;
		wall->height = get_wall_height(left->ground, right->ground,
			left->ceiling, right->ceiling);
		if (left->idx >= DOOR_INDEX)
			wall->is_door = 1;
		else
			wall->is_door = 0;
		wall->next = NULL;
	}
	else
	{
		free(wall);
		wall = NULL;
	}
	return (wall);
}

void	add_point(t_wall **point, t_wall *new)
{
	t_wall	*temp;

	if (new == NULL)
		return ;
	if (*point == NULL)
	{
		*point = new;
	}
	else
	{
		temp = *point;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
}

void	close_linkedlist(t_wall **head)
{
	t_wall	*temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = *head;
}

int	add_points(t_sector *sector,
	unsigned char *buf, unsigned int **pos, ssize_t size)
{
	unsigned int	i;
	t_point_data	data_left;
	t_point_data	data_right;
	t_point_data	data_first;
	t_wall			*wall;

	i = 0;
	if (sector == NULL)
		return (1);
	sector->walls = NULL;
	if (parse_coordinates(&data_left, &pos, &buf, size))
		return (1);
	data_first = data_left;
	while (i < sector->nb_of_walls - 1)
	{
		if (parse_coordinates(&data_right, &pos, &buf, size))
			return (free_points(&sector->walls, i));
		if (data_left.idx < -4 || data_right.idx < -4)
			return (free_points(&sector->walls, i));
		wall = new_point(&data_left, &data_right);
		if (wall)
			add_point(&sector->walls, wall);
		else
			return (free_points(&sector->walls, i));
		data_left = data_right;
		i++;
	}
	data_right = data_first;
	wall = new_point(&data_left, &data_right);
	if (wall)
			add_point(&sector->walls, wall);
		else
			return (free_points(&sector->walls, i));
	close_linkedlist(&sector->walls);
	return (0);
}

t_sector	*get_sector_data(unsigned char *buf, unsigned int *pos, ssize_t size)
{
	t_sector		*new_sector;
	int				ret;

	if (!buf)
		return (NULL);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (NULL);
	if (!ft_strstr((const char *)(buf + *pos), "sector"))
		return (NULL);
	*pos += 6;
	if (*pos > (unsigned int)size)
		return (NULL);
	new_sector = (t_sector *)malloc(sizeof(t_sector));
	if (!new_sector)
		return (NULL);
	if (parse_number_data(new_sector, buf, pos, size))
		return (NULL);
	ret = add_points(new_sector, buf, &pos, size);
	if (ret)
	{
		free(new_sector);
		return (NULL);
	}
	return (new_sector);
}

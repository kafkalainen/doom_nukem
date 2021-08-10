/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:31:08 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/10 11:47:16 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_wall	*new_point(t_point_data *left, t_point_data *right)
{
	t_wall	*wall;

	wall = (t_wall *)malloc(sizeof(*wall));
	if (wall != NULL)
	{
		initialize_wall_triangles(wall, left, right);
		initialize_top_texels(&wall->top);
		initialize_bottom_texels(&wall->bottom);
		initialize_door(wall, left, right);
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
	if (sector == NULL || parse_coordinates(&data_left, &pos, &buf, size))
		return (1);
	data_first = data_left;
	while (i < sector->nb_of_walls)
	{
		if (i + 1 != sector->nb_of_walls
			&& parse_coordinates(&data_right, &pos, &buf, size))
			return (free_points(&sector->walls, i));
		if (i + 1 != sector->nb_of_walls)
			wall = new_point(&data_left, &data_right);
		else
			wall = new_point(&data_left, &data_first);
		if (!wall)
			return (free_points(&sector->walls, i));
		add_point(&sector->walls, wall);
		data_left = data_right;
		i++;
	}
	close_linkedlist(&sector->walls);
	return (0);
}

t_sector	*get_sector_data(unsigned char *buf, unsigned int *pos,
	ssize_t size)
{
	t_sector		*new_sector;

	if (!buf)
		return (NULL);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size
		|| !ft_strnequ((const char *)(buf + *pos), "sector", 6))
		return (NULL);
	*pos += 6;
	if (*pos > (unsigned int)size)
		return (NULL);
	new_sector = (t_sector *)malloc(sizeof(t_sector));
	if (!new_sector)
		return (NULL);
	initialize_sector_pointers(new_sector);
	if (parse_vertex_data(new_sector, buf, pos, size))
		return (free_sector(&new_sector));
	if (add_points(new_sector, buf, &pos, size))
		return (free_sector(&new_sector));
	if (parse_light_data(new_sector, buf, pos, size))
		return (free_sector(&new_sector));
	if (parse_story_data(new_sector, buf, pos, size))
		return (free_sector(&new_sector));
	return (new_sector);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:31:08 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/20 18:46:55 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_point				*new_point(t_xy x0, int idx)
{
	t_point		*new;

	new = (t_point*)malloc(sizeof(*new));
	if (new != NULL)
	{
		new->x0 = x0;
		new->idx = idx;
		new->next = NULL;
	}
	else
	{
		free(new);
		new = NULL;
	}
	return (new);
}

void				add_point(t_point **point, t_point *new)
{
	t_point *temp;

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

void				close_linkedlist(t_point **head)
{
	t_point *temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = *head;
}

int					add_points(t_sector *sector,
	unsigned char *buf, unsigned int **pos)
{
	unsigned int	i;
	t_xy			coord;
	int				tex_id;
	t_point			*point;

	i = 0;
	if (sector == NULL)
		return (1);
	sector->points = NULL;
	while (i < sector->nb_of_walls)
	{
		parse_coordinates(&coord, &tex_id, &pos, &buf);
		if (tex_id < -4)
			return (free_points(&sector->points, i));
		**pos += ft_nb_len(tex_id, 10) + 1;
		point = new_point(coord, tex_id);
		if (point)
			add_point(&sector->points, point);
		else
			return (free_points(&sector->points, i));
		i++;
	}
	close_linkedlist(&sector->points);
	return (0);
}

t_sector			*get_sector_data(unsigned char *buf, unsigned int *pos)
{
	t_sector		*new_sector;
	int				ret;

	if (!buf)
		return (NULL);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (!ft_strstr((const char*)(buf + *pos), "sector"))
		return (NULL);
	*pos += 6;
	if (!(new_sector = (t_sector*)malloc(sizeof(t_sector))))
		return (NULL);
	parse_number_data(new_sector, buf, pos);
	if ((ret = add_points(new_sector, buf, &pos)))
	{
		free(new_sector);
		return (NULL);
	}
	return (new_sector);
}

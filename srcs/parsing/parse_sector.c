/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:32:52 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/20 16:11:31 by jnivala          ###   ########.fr       */
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

t_point				*add_point(t_point **point, t_point *new)
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

t_point				*add_points(t_sector *sector, unsigned char *buf, unsigned int  **pos)
{
	size_t		walls;
	t_point		*temp;
	t_xy		coord;
	int			tex_id;

	walls = sector->nb_of_walls;
	sector->points = NULL;
	while (walls--)
	{
		coord.x = ft_atoi(buf + **pos);
		**pos += ft_numlen(coord.x) + 1;
		coord.y = ft_atoi(buf + **pos);
		**pos += ft_numlen(coord.y) + 1;
		tex_id = ft_atoi(buf + **pos);
		**pos += ft_numlen(tex_id) + 1;
		add_point(&sector->points, new_point(coord, tex_id));
	}
	temp = sector->points;
	while (temp->next)
		temp = temp->next;
	temp->next = sector->points;
}

t_sector			*get_sector_data(unsigned char *buf, unsigned int *pos)
{
	t_sector		*new_sector;

	if (!buf)
		return (NULL);
	if (!(new_sector = (t_sector*)malloc(sizeof(t_sector))))
		error_output("ERROR: Memory allocation for a sector failed.");
	*pos += get_next_breaker(buf + *pos) + 1;
	if (!ft_strstr((const char*)(buf + *pos), "sector"))
		error_output("ERROR: Uncorrect number of sectors given");
	*pos += 6;
	new_sector->idx_sector = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->idx_sector) + 1;
	new_sector->nb_of_walls = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->nb_of_walls) + 1;
	new_sector->ground = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->ground) + 1;
	new_sector->ceiling = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->ceiling) + 1;
	new_sector->tex_floor = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->tex_floor) + 1;
	new_sector->tex_ceil = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->tex_ceil) + 1;
	add_points(new_sector, buf, &pos);
	return (new_sector);
}

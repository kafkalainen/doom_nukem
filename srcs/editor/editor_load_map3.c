/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_load_map3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:20:40 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/11 15:14:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int				editor_get_map_header(unsigned int *pos, unsigned char *buf,
		t_editor *editor, ssize_t size)
{
	int	linked;
	int	nbr_of_sectors;

	nbr_of_sectors = 0;
	linked = 0;
	if (get_next_int_value(&nbr_of_sectors, buf, &pos, size))
		return (-1);
	if (get_next_int_value(&editor->end_sector, buf, &pos, size))
		return (-1);
	if (nbr_of_sectors <= 0 || editor->end_sector <= 0)
		return (-1);
	if (get_next_int_value(&linked, buf, &pos, size))
		return (-1);
	if (linked)
	{
		if (editor_parse_map_name(editor, size, buf, &pos))
			return (-1);
	}
	return (nbr_of_sectors);
}

int				editor_get_player_position(unsigned int *pos,
				unsigned char *buf, t_plr_pos *plr, ssize_t size)
{
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	plr->x = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	plr->z = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	plr->sector = ft_atoi((const char *)buf + *pos);
	return (0);
}

int				editor_parse_vertex_data(t_editor_sector *new,
				unsigned char *buf, unsigned int *pos, ssize_t size)
{
	new->idx_sector = ft_atoi((const char *)buf + *pos);
	if (get_next_int_value(&new->nb_of_walls, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->tex_floor, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->tex_ceil, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->is_elevator, buf, &pos, size))
		return (1);
	*pos += get_next_breaker(buf + *pos);
	if (*pos > (unsigned int)size)
		return (1);
	return (0);
}

t_editor_walls	*editor_new_point(t_point_data *data)
{
	t_editor_walls	*new;

	new = (t_editor_walls *)malloc(sizeof(t_editor_walls));
	if (new != NULL)
	{
		new->x0.x = data->x;
		new->x0.y = data->y;
		new->type = data->idx;
		new->bbox.start = vec2(new->x0.x - 0.2f, new->x0.y + 0.2f);
		new->bbox.end = vec2((new->x0.x + 0.2f), (new->x0.y - 0.2f));
		new->height.ground = data->ground;
		new->height.ceiling = data->ceiling;
		new->next = NULL;
	}
	else
	{
		free(new);
		new = NULL;
	}
	return (new);
}

int	editor_parse_coordinates(t_point_data *data,
	unsigned int ***pos, unsigned char **buf, ssize_t size)
{
	***pos += 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->x = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos) + 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->y = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos) + 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->idx = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos) + 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->ground = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos) + 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->ceiling = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos);
	if (***pos > (unsigned int)size)
		return (1);
	return (0);
}

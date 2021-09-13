/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_load_map5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:20:40 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/13 12:04:22 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	editor_get_sector_data(unsigned char *buf, unsigned int *pos,
	ssize_t size, t_editor_sector **head)
{
	t_editor_sector	*new;

	new = editor_add_new_sector_to_list_end(head);
	if (!buf)
		return (1);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size
		|| !ft_strnequ((const char *)(buf + *pos), "sector", 6))
		return (1);
	*pos += 6;
	if (*pos > (unsigned int)size)
		return (1);
	new->walls = NULL;
	new->plot_line = NULL;
	if (editor_parse_vertex_data(new, buf, pos, size))
		return (1);
	if (editor_add_points(new, buf, &pos, size))
		return (1);
	if (editor_parse_light_data(new, buf, pos, size))
		return (1);
	if (editor_parse_story_data(new, buf, pos, size))
		return (1);
	return (0);
}

int	editor_parse_sector_data(t_editor *editor, unsigned char *buf, ssize_t size)
{
	unsigned int	pos;
	int				i;
	int				nbr_of_sectors;

	i = 0;
	pos = 0;
	buf = (unsigned char *)ft_strstr((const char *)buf, "doom_nukem_sectors");
	if (!buf)
		return (1);
	nbr_of_sectors = editor_get_map_header(&pos, buf, editor, size);
	if (nbr_of_sectors < 0)
		return (1);
	if (editor_get_player_position(&pos, buf, &editor->plr, size))
		return (1);
	while (i < nbr_of_sectors)
	{
		if (editor_get_sector_data(buf, &pos, size, &editor->sector_list))
			error_output("Something went wrong while reading sector data\n");
		i++;
	}
	pos += get_next_breaker(buf + pos);
	if (pos > (unsigned int)size
		|| !ft_strnequ((const char *)buf + pos, "#doom_nukem_entities", 20))
		error_output("ERROR: Invalid data ender for entities.");
	return (0);
}

int	editor_check_entity_data_header(unsigned char **buf, unsigned int *pos,
	ssize_t size)
{
	int	i;

	i = 0;
	*buf = (unsigned char *)ft_strstr((const char *)*buf,
			"doom_nukem_entities");
	if (!*buf)
		error_output("ERROR: Invalid data buffer for entity data.");
	*pos += get_next_breaker(*buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		error_output("ERROR: Invalid buffer length.");
	i = ft_atoi((const char *)*buf + *pos);
	return (i);
}

Uint32	editor_parse_coordinate(t_editor_xyz *coord, unsigned char *buf,
				unsigned int **pos, ssize_t size)
{
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	coord->x = ft_atoi((const char *)buf + **pos);
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	coord->z = ft_atoi((const char *)buf + **pos);
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	coord->y = ft_atoi((const char *)buf + **pos);
	return (0);
}

int	editor_get_entity_data(unsigned char *buf, t_entity_list *entity,
		unsigned int *pos, ssize_t size)
{
	if (get_next_int_value(&entity->entity_type, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->sector_idx, buf, &pos, size))
		return (1);
	if (editor_parse_coordinate(&entity->pos, buf, &pos, size))
		return (1);
	if (editor_parse_coordinate(&entity->dir, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->is_static, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->is_active, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->is_revealed, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->state, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->is_linked, buf, &pos, size))
		return (1);
	entity->bbox.start = vec2(entity->pos.x - 0.2f, entity->pos.z + 0.2f);
	entity->bbox.end = vec2(entity->pos.x + 0.2f, entity->pos.z - 0.2f);
	return (0);
}

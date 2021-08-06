/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entity_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 11:46:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/06 11:53:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	Parse entity data parses following map data:
**	entity_index
**	entity_type	sector_idx	pos			dir			is_static	is_active
**	#enum entity	int		#x#z#y		#x#z#y		boolean		boolean
**	#4				2		#0#10#2		#1#0#2		#1			#1
**	#0				0		#-1#1#2		#1#0#2		#0			#1
**
**	always_facing_plr	is_revealed			state		is_linked
**	boolean				boolean				boolean		Uint32
**	#0					#0					#0			#2
**	#0					#0					#1			#0
*/
static int	get_entity_header_data(unsigned int *pos, unsigned char *buf,
	t_home *home, ssize_t size)
{
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	home->nbr_of_entities = ft_atoi((const char *)buf + *pos);
	return (0);
}

static Uint32	parse_coordinate(t_xyz *coord, unsigned char *buf,
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
	coord->w = 1.0f;
	return (0);
}

static t_entity	*get_entity_data(unsigned char *buf, unsigned int idx,
		unsigned int *pos, ssize_t size)
{
	t_entity	*entity;

	entity = (t_entity *)malloc(sizeof(t_entity));
	if (!entity)
		return (NULL);
	entity->entity_index = idx;
	if (get_next_uint_value(&entity->entity_type, buf, &pos, size))
		return (NULL);
	if (get_next_int_value(&entity->sector_idx, buf, &pos, size))
		return (NULL);
	if (parse_coordinate(&entity->pos, buf, &pos, size))
		return (NULL);
	if (parse_coordinate(&entity->dir, buf, &pos, size))
		return (NULL);
	if (get_next_uint_value(&entity->is_static, buf, &pos, size))
		return (NULL);
	if (get_next_uint_value(&entity->is_active, buf, &pos, size))
		return (NULL);
	if (get_next_uint_value(&entity->always_facing_plr, buf, &pos, size))
		return (NULL);
	if (get_next_uint_value(&entity->is_revealed, buf, &pos, size))
		return (NULL);
	if (get_next_uint_value(&entity->state, buf, &pos, size))
		return (NULL);
	if (get_next_uint_value(&entity->is_linked, buf, &pos, size))
		return (NULL);
	return (entity);
}

int	parse_entity_data(unsigned char *buf, t_home *home, ssize_t size)
{
	unsigned int	pos;
	unsigned int	i;

	i = 0;
	pos = 0;
	buf = (unsigned char *)ft_strstr((const char *)buf, "doom_nukem_entities");
	if (!buf || get_entity_header_data(&pos, buf, home, size))
		return (1);
	home->entity_pool = (t_entity **)malloc(sizeof(t_entity)
			* (home->nbr_of_entities + 1));
	if (!home->entity_pool)
		return (1);
	while (i < home->nbr_of_entities)
	{
		home->entity_pool[i] = get_entity_data(buf, i, &pos, size);
		if (home->entity_pool[i] == NULL)
			error_output("ERROR: Memory allocation for an entity failed.");
		i++;
	}
	pos += get_next_breaker(buf + pos);
	if (pos > (unsigned int)size
		|| !ft_strnequ((const char *)buf + pos, "#doom_nukem_textures", 20))
		return (free_sectors_and_exit(2, home));
	home->entity_pool[i] = NULL;
	return (0);
}

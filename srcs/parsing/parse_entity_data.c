/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entity_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 11:46:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/12 16:43:42 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	Parse entity data parses following map data:
**	entity_index
**	entity_type	sector_idx	pos			dir			is_static	is_active
**	#enum entity	int		#x#z#y		#x#z#y		boolean		boolean
**	#4				#2		#0#10#2		#1#0#2		#1			#1
**	#0				#0		#-1#1#2		#1#0#2		#0			#1
**
**	always_facing_plr	is_revealed			state		is_linked
**	boolean				boolean				boolean		Uint32
**	#0					#0					#0			#2
**	#0					#0					#1			#0
*/

static void	check_entity_data_header(unsigned char **buf, unsigned int *pos,
			t_home *home, ssize_t size)
{
	*buf = (unsigned char *)ft_strstr((const char *)*buf,
			"doom_nukem_entities");
	if (!*buf)
		error_output("ERROR: Invalid data buffer for entity data.");
	*pos += get_next_breaker(*buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		error_output("ERROR: Invalid buffer length.");
	home->nbr_of_entities = ft_atoi((const char *)*buf + *pos);
	home->entity_pool = (t_entity **)malloc(sizeof(t_entity *)
			* (home->nbr_of_entities + 1));
	if (!home->entity_pool)
		error_output("ERROR: Memory allocation for entity pool failed.");
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

static t_entity	*get_entity_data(unsigned char *buf, t_entity *entity,
		unsigned int *pos, ssize_t size)
{
	if (get_next_uint_value(&entity->type, buf, &pos, size))
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
	check_entity_data_header(&buf, &pos, home, size);
	while (i < home->nbr_of_entities)
	{
		home->entity_pool[i] = (t_entity *)ft_memalloc(sizeof(t_entity));
		home->entity_pool[i]->entity_index = i;
		if (home->entity_pool[i] == NULL)
			error_output("ERROR: Memory allocation for an entity failed.");
		home->entity_pool[i] = get_entity_data(buf,
				home->entity_pool[i], &pos, size);
		if (home->entity_pool[i] == NULL)
			error_output("ERROR: Data reading for an entity failed.");
		i++;
	}
	home->entity_pool[i] = NULL;
	pos += get_next_breaker(buf + pos);
	if (pos > (unsigned int)size
		|| !ft_strnequ((const char *)buf + pos, "#doom_nukem_textures", 20))
		error_output("ERROR: Invalid data ender for entities.");
	return (0);
}

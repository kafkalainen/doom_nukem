/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entity_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 11:46:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/28 16:29:15 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	get_entity_header_data(unsigned int *pos, unsigned char *buf,
	t_home *home, ssize_t size)
{
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	home->nbr_of_entities = ft_atoi((const char *)buf + *pos);
	return (0);
}
//In mapdata, example of enemy first, and button as second
//entity_type	sector_idx	pos		dir		is_static	is_active	always_facing_plr	is_revealed	state
//#enum	entity	int			#x#z#y	#x#z#y	boolean		boolean		boolean				boolean		boolean
//#4			2			#0#10#2	#1#0#2	#0			#1			#0					#0			#0
//#0			0			#-1#1#2	#1#0#2	#1			#1			#0					#0			#1


//Issued later.
// float		velocity; // can be looked up via macros
// t_triangle	top; // calculated per frame
// t_triangle	bot; // calculated per frame
// Uint32		take_damage; // boolean to see if we took damage this tick
// Uint32		cooldown; // wait time between moving between idle and move states, or cooldown between attacks
// Uint32		is_revealed; // the twist; if true, set sprite_index to alt_sprite_index, default == false;
// Uint32		entity_type; // 0 == health_station; 1 == enemy_1; 2 == enemy_2;
// Uint32		state;
// Uint32		is_aggroed; // default false, based on distance between entity and player, if within distance parameters, cast ray to see if we can see enemy
// 						// if true, aggro = true
// int			sprite_index; // determined by entity_type // ALWAYS >= 0 // what sprite texture are we drawing from
// int			alt_sprite_index; // default = 0
// int			sprite_state; // angle between player and entity determines X axis of sprite map
// int			anim_offset; // determines Y axis of sprite map
// int			health; // 1 or 2 // determined by entity_type
// int			ammo; // defaults to 3
// int			entity_index; // entity position in the entity_pool array, used to track ammo counts and replenishment
static t_entity	*get_entity_data(unsigned char *buf, unsigned int *pos, ssize_t size)
{
	// t_entity_data	data;
	t_entity	*entity;

	(void)buf;
	(void)pos;
	(void)size;
	entity = (t_entity*)malloc(sizeof(t_entity));
	// *pos += get_next_breaker(buf + *pos) + 1;
	// if (*pos > (unsigned int)size)
	// 	return (1);
	// home->nbr_of_entities = ft_atoi((const char *)buf + *pos);
	return (entity);
}

int	parse_entity_data(unsigned char *buf, t_player *plr,
	t_home *home, ssize_t size)
{
	unsigned int	pos;
	unsigned int	i;

	i = 0;
	pos = 0;
	(void)plr;
	buf = (unsigned char *)ft_strstr((const char *)buf, "doom_nukem_entities");
	if (!buf || get_entity_header_data(&pos, buf, home, size))
		return (1);
	home->entity_pool = (t_entity **)malloc(sizeof(t_entity)
		* (home->nbr_of_entities + 1));
	if (!home->entity_pool)
		return (1);
	while (i < home->nbr_of_entities)
	{
		home->entity_pool[i] = get_entity_data(buf, &pos, size);
		if (home->entity_pool[i] == NULL)
			error_output("ERROR: Memory allocation for a sector failed.");
		i++;
	}
	pos += get_next_breaker(buf + pos);
	if (pos > (unsigned int)size
		|| !ft_strnequ((const char *)buf + pos, "#doom_nukem_textures", 20))
		return (free_sectors_and_exit(2, home));
	home->entity_pool[i] = NULL;
	return (0);
}

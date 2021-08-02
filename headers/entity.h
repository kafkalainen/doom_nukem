/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:51:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/08/02 12:31:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# define AGGRO_RANGE_1 10
# define AGGRO_RANGE_2 20
# define ENTITY_VELOCITY_1 0.005f
# define ENTITY_VELOCITY_2 0.0025f
# define PROJECTILE_VELOCITY 50
# define ENTITY_WIDTH 128
# define ENTITY_HEIGH 128
# define SPRITE_COUNT 7
# define ENTITY_COOLDOWN_1 6
# define ENTITY_COOLDOWN_2 10
# define ENTITY_MOVE 1
# define ENTITY_IDLE 0
# define ENTITY_ATTACK 2
# define ENTITY_TAKE_DAMAGE 3
# define ENTITY_DEAD 4
# define ENTITY_SPRITE_MOVE_START 0 // determine which sprite from sprite map to draw
# define ENTITY_SPRITE_MOVE_END 5 // are we done drawing movement
# define ENTITY_SPRITE_ATK_START 0
# define ENTITY_SPRITE_ATK_END 5

enum e_entities
{
	skull_skulker,
	thing,
	drone,
	crewmember,
	button,
	powerstation,
	lamp,
};

/*
** Entity functions
*/

// move() need pathfinding algorithm
// attack()
// take_damage()
// die()
int			check_aggro(t_player *plr, t_entity *entity, t_sector *sector);
// void		move_entity(t_entity *entity, t_sector *sector, Uint32 delta_time);
void		determine_angle_between_entity_and_plr(t_entity *entity, t_player *plr);
int			entity_move(t_entity *entity, t_home *home, Uint32 t);
void		entity_chase(t_entity *entity, t_home *home, Uint32 t, t_player *plr);
float		get_distance_squared(t_xyz pt0, t_xyz pt1);
Uint32		initialize_entity_textures(t_entity *entity);

#endif

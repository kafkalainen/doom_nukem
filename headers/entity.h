/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:51:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/23 15:19:39 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# define AGGRO_RANGE_1 10
# define AGGRO_RANGE_2 20
# define ENTITY_VELOCITY_1 10
# define ENTITY_VELOCITY_2 25
# define PROJECTILE_VELOCITY 50
# define ENTITY_WIDTH 128
# define ENTITY_HEIGH 128
# define SPRITE_COUNT 7
# define ENTITY_COOLDOWN_1 6
# define ENTITY_COOLDOWN_2 10
# define ENTITY_MOVE 1
# define ENTITY_IDLE 0
# define ENTITY_ATTACK 2
# define ENTITY_TAKE_DAMAGE 4

typedef struct	s_entity
{
	t_xyz		pos;
	t_xyz		normal;
	t_xyz		move_dir;
	float		velocity; // can be looked up via macros
	t_triangle	top; // calculated per frame
	t_triangle	bot; // calculated per frame
	Uint32		take_damage; // boolean to see if we took damage this tick
	Uint32		cooldown; // wait time between moving between idle and move states, or cooldown between attacks
	Uint32		is_static; // 0 == can move, 1 == cannot move
	Uint32		is_active;
	Uint32		always_facing_plr; // if true, always draw entity_front.png OR entity_attack
	Uint32		is_revealed; // the twist; if true, set sprite_index to alt_sprite_index, default == false;
	Uint32		entity_type; // 0 == health_station; 1 == enemy_1; 2 == enemy_2;
	Uint32		state; // 0 == waiting; 1 == move; 2 == attack; 3 == dead // default = 0
	Uint32		is_aggroed; // default false, based on distance between entity and player, if within distance parameters, cast ray to see if we can see enemy
							// if true, aggro = true
	int			sprite_index; // determined by entity_type // ALWAYS >= 0 // what sprite texture are we drawing from
	int			alt_sprite_index; // default = 0
	int			sprite_state; // look at state, then loop through sprite map indexes depeding on the state
	int			health; // 1 or 2 // determined by entity_type
	int			ammo; // defaults to 3
	int			entity_index; // entity position in the entity_pool array, used to track ammo counts and replenishment
	int			sector_idx;
}				t_entity;

typedef	struct	s_projectile
{
	t_xyz		coordinates;
	t_xyz		normal;
	t_xyz		move_dir;
	float		velocity;
	t_triangle	top;
	t_triangle	bot;
	Uint32		is_active;
	Uint32		entity_type; // 0 or 1
	int			sprite_index;
	int			entity_index; // links back to original entity
	int			sprite_state; // determines which sprite to draw from the sprite map
	int			sector_idx;
}				t_projectile;

/*
** Entity functions
*/

// move() need pathfinding algorithm
// attack()
// take_damage()
// die()
void	check_aggro(t_xyz plr_pos, t_entity *entity);


#endif

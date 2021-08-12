/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:51:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/08/12 15:36:06 by jnivala          ###   ########.fr       */
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
# define ENTITY_COOLDOWN_3 20
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
	light_button,
	elevator_button,
	powerstation,
	lamp,
};

enum e_floors
{
	normal_room,
	elevator,
	lower,
	upper
};

enum e_door_states
{
	unlocked,
	locked,
	cleaning_keycard,
	engineering_keycard,
	military_keycard
};

enum e_entity_states
{
	in_front,
	front_left,
	left,
	back_left,
	back,
	back_right,
	right,
	front_right,
	attack,
	die
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
void		translate_entity(t_triangle *tri1, t_triangle *tri2,
				t_entity *entity);
Uint32		handle_activation(t_entity *entity, t_home *home, t_player *plr);
void		turn_on_lights(t_entity *entity, t_home *home);
void		activate_elevator(t_home *home, t_entity *entity, t_player *plr);
Uint32		update_elevators(t_home *home, t_player *plr,
			Uint32 current_time, Uint32 delta_time);
Uint32		translate_sector(t_sector *sector, float distance);
void		translate_entities(t_home *home, float distance, int sector_idx);
Uint32		lock_elevator(t_home *home, t_sector *elevator);
void		bolt_elevator_doors(t_sector *sector, Uint32 state);
void		bolt_elevator_door(t_sector *elevator, t_sector **sectors,
			Uint32 previous_floor, Uint32 state);
void		lock_the_door(t_wall *dimensions, t_wall *door);
void		set_entity_texels_for_frame(t_entity *entity);
void		update_enemies(t_home *home, t_player *plr, Uint32 delta_time);
#endif

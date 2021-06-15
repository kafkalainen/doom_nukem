/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:51:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/15 14:34:16 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

typedef struct	s_entity
{
	t_xyz		coordinates;
	t_xyz		normal;
	float		velocity;
	t_triangle	top;
	t_triangle	bot;
	Uint32		is_static; // 0 == can move, 1 == cannot move
	Uint32		is_revealed; // the twist; if true, set sprite_index to alt_sprite_index, default == false;
	Uint32		entity_type; // 0 == health_station; 1 == enemy_1; 2 == enemy_2;
	Uint32		state; // 0 == waiting; 1 == move; 2 == attack; 3 == dead
	int			sprite_index; // 
	int			alt_sprite_index;
	int			health; // 1 or 2
	int			ammo; // defaults to 3
	int			entity_index; // entity position in the entity_pool array, used to track ammo counts and replenishment
}				t_entity;

typedef	struct	s_projectile
{
	t_xyz		coordinates;
	t_xyz		normal;
	float		velocity;
	t_triangle	top;
	t_triangle	bot;
	Uint32		is_active;
	Uint32		entity_type; // 0 or 1
	int			sprite_index;
	int			sprite_index_explosion; // on hit use this sprite map
	int			entity_index; // links back to original entity
}				t_projectile;


#endif

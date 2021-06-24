/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:51:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/24 14:06:14 by rzukale          ###   ########.fr       */
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
# define ENTITY_TAKE_DAMAGE 3
# define ENTITY_DEAD 4
# define ENTITY_SPRITE_MOVE_START 0 // determine which sprite from sprite map to draw
# define ENTITY_SPRITE_MOVE_END 5 // are we done drawing movement
# define ENTITY_SPRITE_ATK_START 0
# define ENTITY_SPRITE_ATK_END 5

/*
** Entity functions
*/

// move() need pathfinding algorithm
// attack()
// take_damage()
// die()
int		check_aggro(t_player *plr, t_entity *entity, t_sector *sector);


#endif

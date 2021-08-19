/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:39:02 by tmaarela          #+#    #+#             */
/*   Updated: 2021/08/19 10:52:49 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

typedef struct s_window
{
	SDL_Window		*window;
	SDL_Surface		*ScreenSurface;
	int				width;
	int				height;
}					t_window;

/*
**	Entities are structures, that have necessary data to create
**	enemy and objects to the level.
**	top	bot: 			triangles that are calculated per frame based
**						on their direction and position.
**	velocity:			their current velocity.
**	take_damage:		ticks out when enemies take damage.
**	cooldown:			the wait time between idle and move states, when
**						enemy is moving.
**	is_static:			Boolean to for if object is moving or static.
**	always_facing:		If true, always draw entity_front.png
**						OR entity_attack
**	is_revealed:		Enemies have alternate texture pack, then sprite_index
**						is set to alt_sprite_index, default == false;
**	entity_type:		Entity_type is used based on values listed in enum
**						e_entity.
**	state:				State tells if a light switch is on or not, is button
**						activated or not.
**	is_aggroed:			Default false, based on distance between entity and
**						player, if within distance parameters, cast ray
**						to see if we can see enemy. If enemy has a line
**						of sight, set aggro = true
**	entity_index:		Default texture_index. Always >= 0
**	alt_sprite_index:	Storage for alternate texture index. Always >= 0
**	sprite_state:		Angle between player and entity determines X axis
**						of the sprite map.
**	anim_offset:		Tells which frame we are drawing from Y axis of
**						the sprite map.
**	health:				Tells how much health entity has. All entities
**						default to 999, except for enemies that have
**						either 1 or 2 health.
**	ammo:				Ammo defaults to 3 with enemies.
**	entity_pool:		Entity position in the entity_pool array,
**						used to track ammo counts and replenishment.
**	sector_idx:			Tells in which sector entity currently is.
*/

typedef struct	s_entity
{
	t_triangle	top;
	t_triangle	bot;
	t_xyz		pos;
	t_xyz		test_pos;
	t_xyz		dir;
	t_xy		vec_to_plr;
	float		velocity;
	float		height;
	float		width;
	float		legs;
	Uint32		take_damage;
	Uint32		is_static;
	Uint32		is_active;
	Uint32		is_linked;
	Uint32		always_facing_plr;
	Uint32		is_revealed;
	Uint32		entity_type;
	Uint32		state;
	Uint32		is_aggroed;
	int			cooldown;
	int			sprite_index;
	int			alt_sprite_index;
	int			sprite_state;
	int			anim_offset;
	int			health;
	int			ammo;
	int			entity_index;
	int			sector_idx;
}				t_entity;

/*
**	entity_type:	0 or 1
**	entity_index	links back to original entity
**	sprite_state:	determines which sprite to draw from the sprite map.
*/
typedef	struct	s_projectile
{
	t_xyz		pos;
	t_xyz		normal;
	t_xyz		move_dir;
	float		velocity;
	t_triangle	top;
	t_triangle	bot;
	Uint32		is_active;
	Uint32		entity_type;
	int			sprite_index;
	int			entity_index;
	int			sprite_state;
	int			sector_idx;
}				t_projectile;

typedef struct s_home
{
	t_window		win;
	t_skybox		skybox;
	t_sector		**sectors;
	SDL_Surface		*text_surf;
	t_texture		**textures;
	t_texture		**sprites;
	t_entity		**entity_pool;
	t_projectile	**projectile_pool;
	t_time			t;
	t_xy			offset;
	char			**story;
	char			*chosen_map;
	Uint32			linked_map;
	Uint32			nbr_of_entities;
	Uint32			nbr_of_projectiles;
	unsigned int	nbr_of_sectors;
	int				nbr_of_textures;
	int				end_sector;
	int				game_state;
}					t_home;

typedef struct	s_arg
{
	Uint32			*buffer;
	float			*depth_buffer;
	t_texture		**textures;
	t_raster_queue	*view_list;
	t_raster_queue	**raster_queue;
	t_sides			*viewport;
	Uint32			last_frame;
	int				thread_index;
}				t_arg;

typedef struct s_draw_data
{
	Uint32		*buffer;
	float		*depth_buffer;
}				t_draw_data;
#endif

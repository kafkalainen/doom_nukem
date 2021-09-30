/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:39:02 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/30 15:58:25 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

typedef struct s_window
{
	SDL_Window		*window;
	SDL_Surface		*screen;
	int				width;
	int				height;
}					t_window;

typedef struct s_buffer
{
	int				width;
	int				height;
	float			lightness;
	Uint32			*pxl_buffer;
}					t_buffer;

typedef struct s_pxl_coords
{
	int				x;
	int				y;
}					t_pxl_coords;
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
**	is_active:			Is enemy dead or not.
**						In items, it tells us whether to render pickupable
**						item or not.
**	is_revealed:		Enemies have alternate texture pack, then sprite_index
**						is set to alt_sprite_index, default == false;
**	type:				Type is used based on values listed in enum
**						e_entity.
**	state:				State tells if a light switch is on or not, is button
**						activated or not, is it upper or lower floor.
**	is_aggroed:			Default false, based on distance between entity and
**						player, if within distance parameters, cast ray
**						to see if we can see enemy. If enemy has a line
**						of sight, set aggro = true
**	is_pickupable:		Default false, based on entity type. If entity_type
**						is pickable by player, we set is_pickupable to true.
**						all pickupables are facing towards player.
**	is_linked:			0	not linked
**						1	automatic
**						2+	linked button entity
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

typedef struct s_entity
{
	t_triangle	top;
	t_triangle	bot;
	t_xyz		pos;
	t_xyz		test_pos;
	t_xyz		dir;
	t_xy		vec_to_plr_2d;
	t_xyz		vec_to_plr;
	float		velocity;
	float		height;
	float		width;
	float		legs;
	Uint32		time;
	t_bool		take_damage;
	t_bool		is_static;
	t_bool		is_active;
	t_uint		is_linked;
	t_bool		is_revealed;
	t_uint		type;
	t_bool		state;
	t_bool		is_aggroed;
	t_bool		is_pickupable;
	int			making_noise;
	int			cooldown;
	int			die_animation;
	int			sprite_index;
	int			alt_sprite_index;
	int			sprite_state;
	int			anim_offset;
	int			health;
	int			ammo;
	int			entity_index;
	int			sector_idx;
}				t_entity;

typedef struct s_time
{
	Uint32	*frame_times;
	Uint32	frame_time_last;
	Uint32	frame_count;
	float	fps;
}				t_time;

/*
**	type:	0 or 1
**	entity_index	links back to original entity
**	sprite_state:	determines which sprite to draw from the sprite map.
*/
typedef struct s_projectile
{
	t_xyz		pos;
	t_xyz		normal;
	t_xyz		move_dir;
	float		velocity;
	t_triangle	top;
	t_triangle	bot;
	t_bool		is_active;
	Uint32		type;
	int			sprite_index;
	int			alt_sprite_index;
	int			entity_index;
	int			sprite_state;
	int			sector_idx;
}				t_projectile;

typedef struct s_bullet_hole
{
	t_xyz			point;
	t_xyz			normal;
	int				sector_idx;
	int				hole_type;
}					t_bullet_hole;

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
	char			*map;
	Uint32			linked_map;
	Uint32			nbr_of_entities;
	Uint32			nbr_of_projectiles;
	int				projectile_idx;
	unsigned int	nbr_of_sectors;
	int				nbr_of_textures;
	int				end_sector;
	int				game_state;
	float			difficulty;
}					t_home;

typedef struct s_arg
{
	t_buffer		*buffer;
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
	t_buffer	*buffer;
	float		*depth_buffer;
}				t_draw_data;
#endif

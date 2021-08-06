/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:39:02 by tmaarela          #+#    #+#             */
/*   Updated: 2021/08/06 09:30:24 by jnivala          ###   ########.fr       */
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
**	is_linked can have following values.
**	0	not linked
**	1	automatic
**	2->	linked button entity
*/
typedef struct	s_entity
{
	t_triangle	top; // calculated per frame
	t_triangle	bot; // calculated per frame
	t_xyz		pos;
	t_xyz		dir;
	float		velocity; // can be looked up via macros
	Uint32		take_damage; // boolean to see if we took damage this tick
	Uint32		cooldown; // wait time between moving between idle and move states, or cooldown between attacks
	Uint32		is_static; // 0 == can move, 1 == cannot move
	Uint32		is_active;
	Uint32		is_linked;
	Uint32		always_facing_plr; // if true, always draw entity_front.png OR entity_attack
	Uint32		is_revealed; // the twist; if true, set sprite_index to alt_sprite_index, default == false;
	Uint32		entity_type; // 0 == health_station; 1 == enemy_1; 2 == enemy_2;
	Uint32		state;
	Uint32		is_aggroed; // default false, based on distance between entity and player, if within distance parameters, cast ray to see if we can see enemy
							// if true, aggro = true
	int			sprite_index; // determined by entity_type // ALWAYS >= 0 // what sprite texture are we drawing from
	int			alt_sprite_index; // default = 0
	int			sprite_state; // angle between player and entity determines X axis of sprite map
	int			anim_offset; // determines Y axis of sprite map
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

typedef struct s_home
{
	t_window		win;
	t_skybox		skybox;
	t_sector		**sectors;
	SDL_Surface		*text_surf;
	t_texture		**textures;
	t_texture		**sprites; // sprite maps for health station, enemy_1, enemy_2, dead_body, doors???
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

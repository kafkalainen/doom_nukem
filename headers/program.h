/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:39:02 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/16 15:29:19 by rzukale          ###   ########.fr       */
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

typedef	struct s_raster_queue
{
	int			front;
	int			rear;
	int			size;
	int			capacity;
	t_triangle	*array;
}				t_raster_queue;

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
	unsigned int	nbr_of_sectors;
	int				nbr_of_textures;
	int				nbr_of_entities;
	int				nbr_of_projectiles;
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

#endif

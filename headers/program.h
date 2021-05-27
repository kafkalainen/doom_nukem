/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:39:02 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/27 20:00:37 by jnivala          ###   ########.fr       */
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
	size_t		size;
	size_t		capacity;
	t_triangle	*array;
}				t_raster_queue;

typedef struct s_home
{
	t_window		win;
	t_sector		**sectors;
	t_sector		**orig_sectors;
	SDL_Surface		*text_surf;
	t_texture		**editor_tex;
	t_time			t;
	t_xy			offset;
	unsigned int	nbr_of_sectors;
	int				nbr_of_textures;
	int				game_state;
	t_triangle		cube[12];
	t_triangle		transformed_cube[12];
	t_triangle		view_cube;
	t_triangle		*triangles_in_view;
	t_raster_queue	*raster_queue;
	t_sides			viewport;
}					t_home;

#endif

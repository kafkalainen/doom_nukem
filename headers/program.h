/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:39:02 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/09 11:21:22 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

typedef	struct		s_item
{
	float			x;
	float			y;
	float			z;
}					t_item;

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Surface		*ScreenSurface;
	int				width;
	int				height;
}					t_window;

typedef struct		s_raycast
{
	t_xy			sideDist;
	t_xy			deltaDist;
	t_xy			step;
	int				side;
	float			perpWallDist;
}					t_raycast;

typedef struct		s_ray_floor
{
	t_xy			plane;
	t_xy			left;
	t_xy			right;
}					t_ray_floor;

typedef struct		s_step
{
	t_xy			cur_step;
	t_xy			step_len;
}					t_step;

typedef struct		s_tex_col
{
	int				scr_col;
	int				tex_col;
	int				top;
	int				bot;
	int				line_height;
	float			step;
	SDL_Surface		*tex;
}					t_tex_col;

typedef struct		s_texture
{
	Uint32			*tex;
	int				pitch;
	int				h;
}					t_texture;

typedef struct		s_wall
{
	t_xy			hit;
	float			distance;
	int				side;
}					t_wall;


typedef struct		s_frame
{
	int				idx;
	float			max_fov;
	float			offset;
	float			min_step;
	int				old_idx;
	SDL_Surface		*draw_surf;
	t_xy			plr_offset;
}					t_frame;

typedef struct		s_home
{
	t_window		win;
	t_sector		**sectors;
	SDL_Surface		*text_surf;
	TTF_Font		*font;
	t_texture		**editor_textures;
	t_time			t;
	t_xy			offset;
}					t_home;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:48:09 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/05 19:30:44 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# define BUFF_SIZE 16

# define MAX_INT (2147483647)
# define MIN_INT (-MAX_INT - 1)
# define MAX_UINT ((unsigned int)-1)
# define MAX_ULONG ((unsigned long)-1)
# define MAX_ULLONG ((unsigned long long)-1)

# define PI (3.1415926535897932384626433832795f)
# define PI_BY_TWO (1.5707963267948966192313216916398f)
# define TWO_PI (6.283185307179586476925286766559f)
# define RAD_TO_DEG (57.295779513082320876798154814105f)
# define DEG_TO_RAD (0.017453292519943295769236907684886f)

# define TRUE (1)
# define FALSE (0)
# define AND (&&)
# define OR (||)

/*
**
*** Keyboard and Mouse macros
**
*/

# define k_esc SDLK_ESCAPE
# define k_space SDLK_SPACE
# define k_ctrl SDLK_LCTRL
# define k_shift SDLK_LSHIFT

# define k_up SDLK_UP
# define k_down SDLK_DOWN
# define k_left SDLK_LEFT
# define k_right SDLK_RIGHT

# define k_w SDLK_w
# define k_s SDLK_s
# define k_a SDLK_a
# define k_d SDLK_d
# define k_q SDLK_q
# define k_e SDLK_e

# include "SDL2/SDL.h"
# include <SDL2/SDL.h>
# include <libc.h>
# include <stdio.h>

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Surface		*ScreenSurface;
	int				width;
	int				height;
}					t_window;

typedef struct		s_map
{
	int				*bitmap;
}					t_map;

typedef struct		s_texture
{
	SDL_Surface		wall;
	SDL_Surface		sprite;
}				t_texture;

typedef struct	s_home
{
	t_window		*win;
	t_map			*map;
	t_texture		*texture;
}				t_home;

typedef struct s_xy
{
	double		x;
	double		y;
}				t_xy;

typedef t_xy	t_range;

typedef struct	s_xyz
{
	double		x;
	double		y;
	double		z;
}				t_xyz;

t_xy			vec2(double x, double y);
t_xy			vec2_add(t_xy a, t_xy b);
t_xy			vec2_dec(t_xy a, t_xy b);
t_xy			vec2_rot(t_xy v, double angle);
t_xy			vec2_norm(t_xy v);
t_xy			vec2_mul(t_xy v, double scalar);
double			vec2_dot(t_xy a, t_xy b);
double			ft_map(double in, t_range from, t_range to);

void			ft_die(char *msg);
SDL_Texture		*new_surface_to_texture(char *filename, SDL_Renderer *ren);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 18:03:42 by tmaarela          #+#    #+#             */
/*   Updated: 2020/09/08 17:40:557 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include "mlx.h"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 500

# define MINIMAP_SIZE 10
# define TEX_SIZE 64
# define WALL_HEIGHT 0.5

# define HORIZONTAL_WALL 1
# define VERTICAL_WALL 0

# define E_KEY_PRESS 2
# define E_KEY_RELEASE 3
# define E_MOUSE_PRESS 4
# define E_MOUSE_RELEASE 5
# define E_MOUSE_MOVE 6
# define E_CLOSE_WIN 17

# define MAP_MAX_LINES 128

# define M_SENS 0.25
# define FOV 90.0
/*
** *
** Basic structs
** *
*/

typedef struct	s_image
{
	void	*ptr;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		line;
	int		endian;
}				t_image;

typedef struct	s_argb
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;
}				t_argb;

typedef struct	s_xy
{
	double x;
	double y;
}				t_xy;

typedef t_xy	t_range;

typedef struct	s_kboard
{
	int left;
	int right;
	int up;
	int down;
	int q;
	int e;
	int space;
	int ctrl;
}				t_kboard;

typedef struct	s_raycast
{
	t_xy	sideDist;
	t_xy	deltaDist;
	t_xy	step;
	int		side;
	double	perpWallDist;
}				t_raycast;

typedef struct	s_tex_col
{
	int		scr_col;
	int		tex_col;
	int		top;
	int		bot;
	int		line_height;
	double	step;
	t_image	*tex;
}				t_tex_col;

/*
** *
** Higher level structs
** *
*/

typedef struct	s_wall
{
	t_xy	hit;
	double	distance;
	int		side;
}				t_wall;

typedef struct	s_me
{
	t_xy pos;
	t_xy dir;
	double height;
}				t_me;

typedef struct	s_map
{
	char	*data[MAP_MAX_LINES];
	t_xy	size;
}				t_map;

typedef struct	s_mouse
{
	t_xy pos;
	t_xy delta;
}				t_mouse;

/*
** *
** Main struct
** *
*/

typedef struct	s_prog
{
	void		*mlx;
	void		*win;
	clock_t		time;
	t_image		image;
	t_image		skybox;
	t_image		floor;
	t_image		wall[4];
	t_me		me;
	t_map		map;
	t_kboard	key;
	t_mouse		mouse;
}				t_prog;

/*
** *
** Keys
** *
*/

enum			e_mouse
{
# ifdef __linux__
	LMB = 1,
	RMB = 3,
	MMB = 2,
	WhDn = 5,
	WhUp = 4
#else
	LMB = 1,
	RMB = 2,
	MMB = 3,
	WhDn = 4,
	WhUp = 5
# endif
};

enum			e_key
{
# ifdef __linux__
	vk_esc = 65307,
	numPlus = 65451,
	numMin = 65453,
	vk_left = 65361,
	vk_right = 65363,
	vk_down = 65364,
	vk_up = 65362,
	ord_q = 113,
	ord_e = 101,
	ord_space = 0,
	ord_ctrl = 0
# else
	vk_esc = 53,
	numPlus = 69,
	numMin = 78,
	vk_left = 123,
	vk_right = 124,
	vk_down = 125,
	vk_up = 126,
	ord_q = 12,
	ord_e = 14,
	ord_space = 49,
	ord_ctrl = 256
# endif
};

// main.c
void			ft_die(const char *error_message);
void			init_map(char *mapname, t_map *map);
void			init_player(t_me *me, t_map *map);
void			setup(char *mapname, t_prog *p);

/*
** *
** Input
** *
*/

// input_events.c
int				keyboard_press(int keycode, t_kboard *key);
int				keyboard_release(int keycode, t_kboard *key);
int				mouse_move(int x, int y, t_prog *p);
int				window_close(t_prog *p);
int				movement(t_prog *p);
// input.c
void			player_rotate(double delta_time, t_kboard *key, t_me *me);
void			player_move(double delta_time, t_kboard *key, t_me *me, t_map *map);
int				valid_location(t_xy pos, t_map *map);

/*
** *
** Draw
** *
*/

void			render(t_prog *p);

t_image			ft_new_image(int *mlx, int width, int height);
t_image			ft_new_xpm_image(int *mlx, char *filename);
int				ft_clear_buffer(t_image *image);
int				ft_draw_line(t_xy start, t_xy end, int color, t_image *image);
int				ft_draw_box(t_xy corner, t_xy size, int color, t_image *image);
void			ft_draw_cbox(t_xy center, int radius, int color, t_image *image);
void			ft_draw_tex_col(t_tex_col *tex, double distance, t_image *image);
int				ft_put_pixel(int x, int y, int color, t_image *image);

int				argb(int a, int r, int g, int b);
t_argb			int2argb(int color);
int				blend_argb(int foreground, int background);
int				argb2int(t_argb color);

void			draw_background(double height, t_image *image);
t_xy			scale(t_xy a);
void			draw_grid(t_prog *p);
void			draw_top_view(t_xy size, t_xy pos, t_xy dir, t_prog *p);

t_wall			cast_ray(t_xy pos, t_xy ray, t_map *map);
t_xy			init_ray(t_xy pos, t_xy plane, t_xy left, double angle);
void			draw_fov(t_prog *p);
int				get_wall_side(t_wall wall, t_prog *p);

int				apply_fog(int color, double distance);
void			ft_draw_tex_col(t_tex_col *tex, double distance, t_image *image);
void			ft_draw_wall(int col, t_wall wall, t_xy ray, t_prog *p);

/*
** *
** Vector math
** *
*/

// vec2.c
t_xy			vec2(double x, double y);
t_xy			vec2_rot(t_xy v, double angle);
t_xy			vec2_norm(t_xy v);
t_xy			vec2_mul(t_xy v, double scalar);
t_xy			vec2_add(t_xy a, t_xy b);
t_xy			vec2_dec(t_xy a, t_xy b);
double			vec2_mag(t_xy v);
double			vec2_dot(t_xy a, t_xy b);
double			vec2_rad(t_xy v);
double			vec2_cross(t_xy a, t_xy b);
double			vec2_slope(t_xy p_a, t_xy p_b);

double			ft_map(double in, t_range from, t_range to);


#endif

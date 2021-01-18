/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:48:09 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/18 11:16:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# define BUFF_SIZE 16
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

# define WALL_HEIGHT 0.5
# define TEX_SIZE 128
# define FOV 90.0
# define MAP_MAX_LINES 128
# define MINIMAP_SIZE 10

# define HORIZONTAL_WALL 1
# define VERTICAL_WALL 0

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



# ifdef __unix__
#  define OPEN_FILE open
#  define READ_ONLY O_RDONLY
#  include "include/SDL2/SDL.h"
#  include <string.h>
#  include <time.h>
#  include <fcntl.h>
#  include <unistd.h>
# elif __APPLE__
#  define OPEN_FILE open
#  define READ_ONLY O_RDONLY
#  include "include/SDL2/SDL.h"
#  include <string.h>
#  include <time.h>
#  include <fcntl.h>
#  include <unistd.h>
# elif defined(_WIN32) || defined(WIN32)
#  define OPEN_FILE _open
#  define READ_ONLY _O_RDONLY
#  include "SDL.h"
#  include <io.h>
#  include <stdio.h>
#  include <time.h>
#  include <fcntl.h>
# endif

typedef struct		s_input
{
	int				right;
	int				left;
	int				up;
	int				down;
}					t_input;


typedef struct		s_argb
{
	int				a;
	int				r;
	int				g;
	int				b;
}					t_argb;

typedef struct		s_time
{
	clock_t			beginfps;
	clock_t			endfps;
	clock_t			delta_time;
	size_t			frames;
	long int		fps;
}					t_time;

typedef struct		s_screen_xy
{
	int				x;
	int				y;
}					t_screen_xy;

typedef struct		s_xy
{
	double			x;
	double			y;
}					t_xy;

typedef t_xy		t_range;

typedef struct		s_xyz
{
	double			x;
	double			y;
	double			z;
}					t_xyz;

typedef	struct		s_item
{
	double			x;
	double			y;
	double			z;
}					t_item;

typedef struct		s_player
{
	t_xy			pos;
	t_xy			dir;
	double			z;
	double			height;
	t_input			input;
	clock_t			time;
}					t_player;

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Surface		*ScreenSurface;
	int				width;
	int				height;
}					t_window;

typedef struct		s_map
{
	float			*bitmap;
	float			*heightmap;
	char			*data[MAP_MAX_LINES];
	t_xy			size;
}					t_map;

typedef struct		s_raycast
{
	t_xy			sideDist;
	t_xy			deltaDist;
	t_xy			step;
	int				side;
	double			perpWallDist;
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
	double			step;
	SDL_Surface		*tex;
}					t_tex_col;

typedef struct		s_texture
{
	SDL_Surface		wall;
	SDL_Surface		sprite;
}					t_texture;

typedef struct		s_wall
{
	t_xy			hit;
	double			distance;
	int				side;
}					t_wall;

typedef struct		s_home
{
	t_window		win;
	t_map			map;
	t_texture		*texture;
	SDL_Renderer	*ren;
	SDL_Surface		*draw_surf;
	SDL_Surface		*wall[4];
	SDL_Surface		*ground;
	t_time			t;
}					t_home;

/*
** Libft functions (recoded libc functions)
*/

int				ft_numlen(long number);
char			*ft_itoa(long long number);

size_t			ft_strlen(const char *str);
size_t			ft_strclen(const char *str, int c);
void			ft_strdel(char **p);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *str);
char			*ft_strcpy(char *dst, const char *str);
int				ft_strcmp(const char *str1, const char *str2);
char			*ft_strsub(const char *str, unsigned int start, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strcat(char *dst, const char *str);
char			*ft_strjoin(const char *s1, const char *s2);

void			*ft_memset(void *dst, int c, size_t n);
void			ft_memdel(void **p);

int				ft_get_next_line(const int fd, char **out);


/*
** Vector functions
*/

t_xy			vec2(double x, double y);
t_xy			vec2_add(t_xy a, t_xy b);
t_xy			vec2_dec(t_xy a, t_xy b);
t_xy			vec2_rot(t_xy v, double angle);
t_xy			vec2_norm(t_xy v);
t_xy			vec2_mul(t_xy v, double scalar);
double			vec2_dot(t_xy a, t_xy b);
double			ft_map(double in, t_range from, t_range to);

/*
** Drawing functions
*/


void			clear_surface(SDL_Surface *surface);
int				ft_put_pixel(double x, double y, int color, SDL_Renderer *ren);
int				ft_draw_line(t_xy start, t_xy end, int color, SDL_Surface *surf);
void			draw_rect_center(t_xy xy, t_xy wh, t_home *home);
void			draw_rect(t_xy xy, t_xy wh, t_home *home, int color);
void			put_pixel(SDL_Surface *surf, int x, int y, int color);
void			modify_pixel_add(SDL_Surface *surf, int x, int y, int color);
Uint32			get_pixel(SDL_Surface *surface, int x, int y);


/*
** Raycaster
*/

void			draw_tex_col(t_tex_col *tex, double distance, SDL_Surface *surf);
void			draw_wall(int col, t_wall wall, t_xy ray, t_home *home, t_player *plr);
void			draw_fov_floor(t_home *home, t_player *plr);

t_xy			init_ray(t_xy pos, t_xy plane, t_xy left, double angle);
t_wall			cast_ray(t_xy pos, t_xy ray, t_map *map);
void			draw_fov(t_home *home, t_player *plr);
int				get_wall_side(t_wall wall, t_player *plr);

/*
** Color manipulation
*/

t_argb			int2argb(int color);

/*
** Player
*/

void			init_player(t_player *plr, t_map *map);
void			update_player(t_player *plr, t_home *home, SDL_Event e);
void			movement(t_player *plr);

/*
** Event handlers
*/

void			key_input(t_player *plr, SDL_Event e, t_home *home);
void			mouse_handle_unix(t_player *plr, t_home *home);
void			mouse_handle_win(t_player *plr);

/*
** Miscellanious
*/

void			update_screen(t_home *home, t_player *plr);
void			setup(char *mapname, t_home *home, t_player *plr);
void			error_output_sdl(char *msg, t_home *home);
void		    error_output(char *msg);

/*
** Minimap
*/

t_xy			scale(t_xy a);
void			draw_minimap(t_xy size, t_xy pos, t_xy dir, t_home *home);
void			draw_grid(t_home *home);


#endif

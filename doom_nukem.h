/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:48:09 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/21 17:15:35 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

/*
**	Non-standard includes
*/


#  include <time.h>
#  include <fcntl.h>

# ifdef __unix__
#  define OPEN_FILE open
#  define READ_ONLY O_RDONLY
#  include <math.h>
#  include "include/SDL2/SDL.h"
#  include <string.h>
#  include <unistd.h>
# elif __APPLE__
#  define OPEN_FILE open
#  define READ_ONLY O_RDONLY
#  include "include/SDL2/SDL.h"
#  include <string.h>
#  include <unistd.h>
# elif defined(_WIN32) || defined(WIN32)
#  define OPEN_FILE _open
#  define READ_ONLY _O_RDONLY
#  include "SDL.h"
#  include <io.h>
#  include <stdio.h>

# endif

# include "macros.h"
# include "vectors.h"
# include "entity.h"
# include "sector.h"
# include "colours.h"
# include "player.h"
# include "calculations.h"
# include "miniaudio.h"


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
	SDL_Surface		wall;
	SDL_Surface		sprite;
}					t_texture;

typedef struct		s_wall
{
	t_xy			hit;
	float			distance;
	int				side;
}					t_wall;

typedef struct		s_home
{
	t_window		win;
	t_map			map;
	t_sector		**sectors;
	t_texture		*texture;
	SDL_Renderer	*ren;
	SDL_Surface		*draw_surf;
	SDL_Surface		*wall[4];
	SDL_Surface		*ground[4];
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
void			ft_putendl_fd(char const *s, int fd);
/*
** Drawing functions
*/


void			clear_surface(SDL_Surface *surface);
int				ft_put_pixel(float x, float y, int color, SDL_Renderer *ren);
int				ft_draw_line(t_xy start, t_xy end, int color, SDL_Surface *surf);
void			draw_rect_center(t_xy xy, t_xy wh, t_home *home);
void			draw_rect(t_xy xy, t_xy wh, t_home *home, int color);
void			put_pixel(SDL_Surface *surf, int x, int y, int color);
void			draw_tex_pixel(SDL_Surface *tex, t_screen_xy pixel,
	t_screen_xy coord, SDL_Surface *draw_surf);
t_step			*steplen(t_step *ground, int current_y, t_ray_floor hor,
	t_player *plr);
void			draw_world_floor(int y, t_player *plr, t_home *home,
	t_ray_floor hor);
void			modify_pixel_add(SDL_Surface *surf, int x, int y, int color);
Uint32			get_pixel(SDL_Surface *surface, int x, int y);


/*
** Raycaster
*/

void			draw_tex_col(t_tex_col *tex, float distance, SDL_Surface *surf);
void			draw_wall(int col, t_wall wall, t_xy ray, t_home *home, t_player *plr);
void			draw_fov_floor(t_home *home, t_player *plr);

t_xy			init_ray(t_xy pos, t_xy plane, t_xy left, float angle);
t_wall			cast_ray(t_xy pos, t_xy ray, t_map *map);
void			draw_fov(t_home *home, t_player *plr);
int				get_wall_side(t_wall wall, t_player *plr);
void			draw_2d(t_home *home, t_player *plr, t_intersection *sect);

/*
** Color manipulation
*/

t_argb			int2argb(int color);

/*
** Player
*/

void			init_player(t_player *plr, t_map *map);
void			update_player(t_player *plr, t_home *home, SDL_Event e);
void			movement(t_player *plr, t_map *map);
void			player_move_forward(t_player *plr, t_map *map, float delta_time);
void			player_move_strafe(t_player *plr, t_map *map, float delta_time, char ad);
void			player_move_backwards(t_player *plr, t_map *map, float delta_time);

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
int				update_sector(t_home *home);

#endif

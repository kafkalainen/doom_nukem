/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zukala <zukaa@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:48:09 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/26 10:23:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <fcntl.h>
# include <dirent.h>
# include <time.h>
# include <math.h>
# ifdef __unix__
#  define OS_WINDOWS 0
#  define READ_ONLY O_RDONLY
#  define WRITE_ONLY O_WRONLY
#  define APPEND_FILE O_APPEND
#  define CHECK_EXIST O_EXCL
#  define CREATE_FILE O_CREAT
#  define TRUNCATE O_TRUNC
#  include <string.h>
#  include <unistd.h>
#  include <pthread.h>
#  include "../SDL2/include/SDL2/SDL.h"
#  include "../SDL2_mixer/include/SDL2/SDL_mixer.h"
#  include "../headers/syscalls_windows.h"
# elif defined(_WIN32) || defined(WIN32)
#  define OS_WINDOWS 1
#  define READ_ONLY _O_BINARY
#  define WRITE_ONLY _O_WRONLY
#  define CHECK_EXIST _O_EXCL
#  define APPEND_FILE _O_APPEND
#  define CREATE_FILE _O_CREAT
#  define TRUNCATE _O_TRUNC
#  include <io.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <pthread.h>
#  include "../SDL2-2.0.14/i686-w64-mingw32/include/SDL2/SDL.h"
#  include "../SDL2_mixer-2.0.4/i686-w64-mingw32/include/SDL2/SDL_mixer.h"

# endif

# include "macros.h"
# include "vectors.h"
# include "sector.h"
# include "colours.h"
# include "parser_structs.h"
# include "png_parser.h"
# include "audio.h"
# include "program.h"
# include "player.h"
# include "entity.h"

# include "../libft/libft.h"
# include "engine.h"
# include "typewriter.h"
# include "editor.h"
# include "drawing_functions.h"
# include "events.h"
# include "porting.h"
# include "parsing.h"
# include "menu_systems.h"

/*
** Miscellaneous
*/

void		clean_up(t_frame *frame);
int			doom_close(int *fd);
ssize_t		doom_write(int *fd, const void **buf, size_t count);
void		doom_open(int *fd, const char **path, int mode, mode_t rights);
void		doom_read(ssize_t *read_bytes, int *fd, void **buf, size_t nb_of_bytes);
int			doom_mkdir(void);
void		draw_text(t_home *home, char *text, t_frame *frame, t_xy pos);
void		error_output(char *msg);
void		error_output_sdl(char *msg, t_home *home, t_frame *frame);
int			free_all(t_frame *frame, t_audio *audio, Uint32 *buffer,
				char **chosen_map);
void		fps_timer(t_time *t);
void		get_map_maximum_values(float *max, t_sector **sectors,
				t_uint nb_of_sectors);
int			give_sign(float number);
int			initialize_rasterization_queues(t_frame *frame);
int			initialize_skybox(t_skybox *skybox, t_sector **sectors,
				t_uint nb_of_sectors);
int			initialize_hud(t_hud *hud);
int			is_negative(float z);
void		map_error_output(int i, t_home *home);
void		read_error_output(char *msg, unsigned char **line);
t_screen_xy	round_coordinates(t_xy	coord);
float		set_valid(float angle);
void		setup(t_home *home, t_player *plr, t_frame *frame, t_menu *menu);
int			setup_fps(t_time *time);
void		translate_world_view(t_home *home, t_xy step);
void		transform_world_view(t_home *home, float delta_dir);
void		update_screen(t_home *home, t_frame *frame, t_player *plr);
void		swap_node_data(t_editor_walls *data_0, t_editor_walls *data_1);
void		swap_sides(t_steps *steps);
void		swap_uvz(t_uvz *p0, t_uvz *p1);
void		swap_xyz(t_xyz *p0, t_xyz *p1);
void		sort_vertices(t_triangle *tri);

#endif

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
# include "time.h"
# include "math.h"
# ifdef __unix__
#  define OS_WINDOWS 0
#  define READ_ONLY O_RDONLY
#  define TEXT_ONLY O_RDONLY
#  define WRITE_ONLY O_WRONLY
#  define APPEND_FILE O_APPEND
#  define CHECK_EXIST O_EXCL
#  define CREATE_FILE O_CREAT
#  define TRUNCATE O_TRUNC
#  include <string.h>
#  include <unistd.h>
#  include "../SDL2/include/SDL2/SDL.h"
#  include "../SDL2_mixer/include/SDL2/SDL_mixer.h"
#  include "../headers/syscalls_windows.h"
# elif __APPLE__
#  define READ_ONLY O_RDONLY
#  include <string.h>
#  include <unistd.h>
# elif defined(_WIN32) || defined(WIN32)
#  define OS_WINDOWS 1
#  define READ_ONLY _O_BINARY
#  define TEXT_ONLY _O_TEXT
#  define WRITE_ONLY _O_WRONLY
#  define CHECK_EXIST _O_EXCL
#  define APPEND_FILE _O_APPEND
#  define CREATE_FILE _O_CREAT
#  define TRUNCATE _O_TRUNC
#  include <io.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include "../SDL2-2.0.14/i686-w64-mingw32/include/SDL2/SDL.h"
#  include "../SDL2_mixer-2.0.4/i686-w64-mingw32/include/SDL2/SDL_mixer.h"

# endif

# include "macros.h"
# include "vectors.h"
# include "entity.h"
# include "sector.h"
# include "calculations.h"
# include "colours.h"
# include "parser_structs.h"
# include "png_parser.h"
# include "program.h"
# include "audio.h"
# include "player.h"

# include "../libft/libft.h"
# include "player_functions.h"
# include "raycast.h"
# include "drawing_functions.h"
# include "caster.h"
# include "events.h"
# include "map.h"
# include "porting.h"
# include "parsing.h"
# include "typewriter.h"

/*
** Miscellanious
*/

void	clean_up(t_home *home);
void	cleanup_audio(t_audio *audio);
int		doom_close(int *fd);
void	doom_open(int *fd, const char **path, int mode, mode_t rights);
void	doom_read(ssize_t *read_bytes, int *fd, void **buf, size_t nb_of_bytes);
void	draw_text(t_home *home, char *text, t_frame *frame, t_xy pos);
void	error_output(char *msg);
void	error_output_sdl(char *msg, t_home *home);
void	fps_timer(t_time *t);
int		load_audio(t_audio *audio);
int		load_game_audio(t_audio *audio);
void	map_error_output(int i, t_home *home);
void	play_footsteps(t_player *plr);
void	read_error_output(char *msg, unsigned char **line);
void	setup(char *mapname, t_home *home, t_player *plr, t_frame *frame);
void	setup_game_loop(char *mapname, t_home *home, t_player *plr, t_frame *frame);
void	translate_world_view(t_home *home, t_xy step);
void	transform_world_view(t_home *home, float delta_dir);
void	update_screen(t_home *home, t_frame *frame, t_player *plr);
#endif

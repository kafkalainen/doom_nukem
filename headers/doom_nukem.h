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
# ifdef __unix__
#  define OPEN_FILE open
#  define READ_FILE read
#  define CLOSE_FILE close
#  define READ_ONLY O_RDONLY
#  define WRITE_ONLY O_WRONLY
#  define APPEND_FILE O_APPEND
#  define CHECK_EXIST O_EXCL
#  define CREATE_FILE O_CREAT
#  define TRUNCATE O_TRUNC
#  include <math.h>
#  include "../SDL2/include/SDL2/SDL.h"
#  include "../SDL2_mixer/include/SDL2/SDL_mixer.h"
#  include <string.h>
#  include <unistd.h>
# elif __APPLE__
#  define OPEN_FILE open
#  define READ_ONLY O_RDONLY
#  include <string.h>
#  include <unistd.h>
# elif defined(_WIN32) || defined(WIN32)
#  define OPEN_FILE _open
#  define READ_FILE _read
#  define CLOSE_FILE _close
#  define READ_ONLY _O_BINARY
#  define WRITE_ONLY _O_WRONLY
#  define CHECK_EXIST _O_EXCL
#  define APPEND_FILE _O_APPEND
#  define CREATE_FILE _O_CREAT
#  define TRUNCATE _O_TRUNC
#  include "SDL2_mixer_win/include/SDL2/SDL_mixer.h"
#  include <io.h>
#  include <stdio.h>

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
# include "porting.h"
# include "parsing.h"
# include "map.h"
# include "typewriter.h"

/*
** Miscellanious
*/

void	cleanup_audio(t_audio *audio);
void	error_output(char *msg);
void	error_output_sdl(char *msg, t_home *home);
void	setup(char *mapname, t_home *home, t_player *plr, t_frame *frame);
int		load_audio(t_audio *audio);
void	map_error_output(int i, t_home *home);
void	play_footsteps(t_player *plr);
void	update_screen(t_home *home, t_frame *frame, t_player *plr);

/*
** Minimap
*/

t_xy			scale(t_xy a);
void			draw_minimap(t_xy size, t_xy pos, t_xy dir, t_home *home);
void			draw_grid(t_frame *frame);
void			translate_world_view(t_home *home, t_xy step);
void			transform_world_view(t_home *home, float delta_dir);
void			trans_world_view(t_home *home, t_xy step, float delta_dir);

void			draw_text(t_home *home, char *text, t_frame *frame, t_xy pos);
#endif

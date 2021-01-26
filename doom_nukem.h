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

/*
**	Non-standard includes
*/

#  include "SDL2/include/SDL2/SDL.h"
#  include <time.h>
#  include <fcntl.h>

# ifdef __unix__
#  define OPEN_FILE open
#  define READ_ONLY O_RDONLY
#  include <math.h>
#  include "/usr/local/include/SDL2/SDL_mixer.h"
#  include <string.h>
#  include <unistd.h>
# elif __APPLE__
#  define OPEN_FILE open
#  define READ_ONLY O_RDONLY
#  include <string.h>
#  include <unistd.h>
# elif defined(_WIN32) || defined(WIN32)
#  define OPEN_FILE _open
#  define READ_ONLY _O_RDONLY
#  include "SDL2_mixer_win/include/SDL2/SDL_mixer.h"
#  include <io.h>
#  include <stdio.h>

# endif

# include "headers/macros.h"
# include "headers/vectors.h"
# include "headers/entity.h"
# include "headers/sector.h"
# include "headers/calculations.h"
# include "headers/colours.h"
# include "headers/program.h"
# include "headers/audio.h"
# include "headers/player.h"

# include "headers/libft.h"
# include "headers/drawing_functions.h"
# include "headers/caster.h"
# include "headers/events.h"
# include "headers/player_functions.h"
# include "headers/porting.h"
# include "headers/parsing.h"
# include "headers/map.h"

/*
** Miscellanious
*/

void			update_screen(t_home *home, t_player *plr);
void			setup(char *mapname, t_home *home, t_player *plr);
void			error_output_sdl(char *msg, t_home *home);
void			error_output(char *msg);
void			load_audio(t_audio *audio);
void			cleanup_audio(t_audio *audio);
void			play_footsteps(t_player *plr);

/*
** Minimap
*/

t_xy			scale(t_xy a);
void			draw_minimap(t_xy size, t_xy pos, t_xy dir, t_home *home);
void			draw_grid(t_home *home);
int				update_sector(t_home *home);

#endif

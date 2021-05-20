/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:39:02 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/20 11:47:57 by rzukale          ###   ########.fr       */
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

typedef	struct		s_buffer
{
	int				width;
	int				height;
	Uint32			*buffer;
}					t_buffer;

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
}					t_home;

#endif

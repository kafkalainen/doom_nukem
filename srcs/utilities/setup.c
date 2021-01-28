/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:17:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/28 12:59:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static t_home	*init_sdl(t_home *home)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		error_output_sdl("Fatal: SDL Initalization failed.", home);
	home->win.window = SDL_CreateWindow("Hello World!", 100, 100,
		home->win.width, home->win.height, 0);
	if (!home->win.window)
		error_output_sdl("Fatal: Failed to create a window.", home);
	SDL_SetWindowPosition(home->win.window,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	home->draw_surf = SDL_GetWindowSurface(home->win.window);
	if (!home->draw_surf)
		error_output_sdl("Fatal: Failed to get window surface", home);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		error_output_sdl("Fatal: SDL_mixer could not initialize!", home);
	return (home);
}

void			init_player(t_player *plr)
{
	plr->pos = vec2(1, 1);
	plr->z = 0;
	plr->dir.x = 1;
	plr->dir.y = 0;
	plr->input.down = 0;
	plr->input.up = 0;
	plr->input.right = 0;
	plr->input.left = 0;
	plr->time = 0;
	plr->height = 0.5;
}

void			setup(char *mapname, t_home *home, t_player *plr)
{
	home->win.width = SCREEN_WIDTH;
	home->win.height = SCREEN_HEIGHT;
	home->t.fps = 0;
	home->t.frames = 0;
	home = init_sdl(home);
	if (TTF_Init() < 0)
		error_output_sdl("Fatal: Failed to init TTF.", home);
	home->font = TTF_OpenFont("arial.ttf", 24);
	if (home->font == NULL)
		error_output_sdl("Fatal: Failed to init given font.", home);
	load_audio(&plr->audio);
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(plr->audio.music, -1);
	/*init_textures(home);*/
	init_player(plr);
}

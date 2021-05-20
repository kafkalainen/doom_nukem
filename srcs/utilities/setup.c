/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:17:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/20 12:15:38 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_home	*init_sdl(t_home *home, float *min_step)
{
	home->win.width = SCREEN_WIDTH;
	home->win.height = SCREEN_HEIGHT;
	// SDL_SetMainReady();
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
		error_output_sdl("Fatal: SDL Initalization failed.", home);
	home->win.window = SDL_CreateWindow("Doom-Nukem", 100, 100,
			home->win.width, home->win.height, 0);
	if (home->win.window == NULL)
		error_output_sdl("Fatal: Failed to create a window.", home);
	SDL_SetWindowPosition(home->win.window,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	home->win.ScreenSurface = SDL_GetWindowSurface(home->win.window);
	if (home->win.ScreenSurface == NULL)
		error_output_sdl("Fatal: Failed to get window surface", home);
	*min_step = 0.002454369f;
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		error_output_sdl("Fatal: SDL_mixer could not initialize!", home);
	return (home);
}

void	init_player(t_player *plr)
{
	plr->pos = vec2(0, 0);
	plr->pitch = 240;
	plr->height = 10;
	plr->dir.x = 0.0f;
	plr->dir.y = 1.0f;
	plr->input.down = 0;
	plr->input.up = 0;
	plr->input.right = 0;
	plr->input.left = 0;
	plr->input.rot_right = 0;
	plr->input.rot_left = 0;
	plr->input.wireframe = 0;
	plr->input.minimap = 1;
	plr->input.info = 1;
	plr->input.mouse = 1;
	plr->time = 0;
	plr->current_sector = 0;
	plr->z = 0;
}

void	setup_fps(t_time *time)
{
	time->frame_times = (Uint32 *)malloc(sizeof(Uint32) * 11);
	if (!time->frame_times)
		error_output("Memory allocation failed!\n");
	time->frame_count = 0;
	time->fps = 0;
	time->frame_time_last = SDL_GetTicks();
}

void	setup(t_home *home, t_player *plr, t_frame *frame, t_menu *menu)
{
	// int		ret;

	home->win.width = SCREEN_WIDTH;
	home->win.height = SCREEN_HEIGHT;
	setup_fps(&home->t);
	home->offset = vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	frame->buffer.pxl_buffer = (Uint32 *)malloc(sizeof(Uint32)
			* (Uint32)SCREEN_WIDTH * (Uint32)SCREEN_HEIGHT);
	if (!frame->buffer.pxl_buffer)
		error_output("Memory allocation failed!\n");
	frame->buffer.width = SCREEN_WIDTH;
	frame->buffer.height = SCREEN_HEIGHT;
	home = init_sdl(home, &frame->min_step);
	// ret = load_audio(&plr->audio);
	// if (ret)
	// {
	// 	cleanup_audio(&plr->audio);
	// 	SDL_Quit();
	// 	clean_up(home);
	// }
	// if (Mix_PlayingMusic() == 0)
	// 	Mix_PlayMusic(plr->audio.music, -1);
	init_player(plr);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	setup_menu(menu, &home->game_state);
}

void	clean_up(t_home *home)
{
	free_sectors(home);
	if (home->t.frame_times)
		free(home->t.frame_times);
	ft_putendl_fd("Shutting down.", 2);
	exit(EXIT_FAILURE);
}

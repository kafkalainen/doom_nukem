/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:17:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/22 09:41:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_home	*init_sdl(t_home *home, t_frame *frame)
{
	home->map = NULL;
	home->win.width = SCREEN_WIDTH;
	home->win.height = SCREEN_HEIGHT;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
		error_output_sdl("Fatal: SDL Initalization failed.", home, frame);
	home->win.window = SDL_CreateWindow("Doom-Nukem", 100, 100,
			home->win.width, home->win.height, 0);
	if (home->win.window == NULL)
		error_output_sdl("Fatal: Failed to create a window.", home, frame);
	SDL_SetWindowPosition(home->win.window,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	home->win.screen = SDL_GetWindowSurface(home->win.window);
	if (home->win.screen == NULL)
		error_output_sdl("Fatal: Failed to get window surface", home, frame);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		error_output_sdl("Fatal: SDL_mixer could not initialize!", home, frame);
	return (home);
}

int	setup_fps(t_time *time)
{
	time->frame_times = (Uint32 *)malloc(sizeof(Uint32) * 11);
	if (!time->frame_times)
		return (1);
	time->frame_count = 0;
	time->fps = 0;
	time->frame_time_last = SDL_GetTicks();
	return (0);
}

/* ADD MENU AUDIO!!
** ret = load_audio(&plr->audio);
** if (ret)
** {
** 	cleanup_audio_source(&plr->audio);
** 	ft_putendl_fd("Failed to load audio files from source,
	proceeding without menu music\n", 2);
** }
** else
** 	if (Mix_PlayingMusic() == 0)
** 		Mix_PlayMusic(plr->audio.music, -1);
*/
void	setup(t_home *home, t_player *plr, t_frame *frame, t_menu *menu)
{
	home->win.width = SCREEN_WIDTH;
	home->win.height = SCREEN_HEIGHT;
	home->offset = vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	frame->buffer.pxl_buffer = (Uint32 *)malloc(sizeof(Uint32)
			* (Uint32)SCREEN_WIDTH * (Uint32)SCREEN_HEIGHT);
	if (!frame->buffer.pxl_buffer)
		error_output("Memory allocation failed!\n");
	frame->buffer.width = SCREEN_WIDTH;
	frame->buffer.height = SCREEN_HEIGHT;
	frame->depth_buffer = (float *)malloc(sizeof(float)
			* (SCREEN_WIDTH * SCREEN_HEIGHT + 1));
	frame->fade = 0.0f;
	if (!frame->depth_buffer)
		error_output("Memory allocation failed for depth buffer!");
	if (initialize_rasterization_queues(frame))
		error_output("Memory allocation failed for rasterizer.");
	frame->sector_buffer = (int *)malloc(sizeof(int) * (3000));
	if (!frame->sector_buffer)
		error_output("Memory allocation failed for sector buffer.");
	home = init_sdl(home, frame);
	initialize_audio_to_null(&plr->audio);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	setup_menu(menu, &home->game_state);
}

void	clean_up(t_frame *frame)
{
	if (frame->buffer.pxl_buffer)
		free(frame->buffer.pxl_buffer);
	free_queues(frame);
	ft_putendl_fd("Shutting down.", 2);
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:17:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/27 12:16:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_home	*init_sdl(t_home *home, t_frame *frame, float *min_step)
{
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
	home->win.ScreenSurface = SDL_GetWindowSurface(home->win.window);
	if (home->win.ScreenSurface == NULL)
		error_output_sdl("Fatal: Failed to get window surface", home, frame);
	*min_step = 0.002454369f;
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		error_output_sdl("Fatal: SDL_mixer could not initialize!", home, frame);
	return (home);
}

void	initialize_player_target_triangles(t_player *plr)
{
	plr->tri[0].p[0] = (t_xyz){-0.5f * plr->width,
		-0.5f * plr->height, 0.0f, 1.0f};
	plr->tri[0].p[1] = (t_xyz){-0.5f * plr->width,
		0.5f * plr->height, 0.0f, 1.0f};
	plr->tri[0].p[2] = (t_xyz){0.5f * plr->width,
		0.5f * plr->height, 0.0f, 1.0f};
	plr->tri[1].p[0] = (t_xyz){-0.5f * plr->width,
		-0.5f * plr->height, 0.0f, 1.0f};
	plr->tri[1].p[1] = (t_xyz){0.5f * plr->width,
		0.5f * plr->height, 0.0f, 1.0f};
	plr->tri[1].p[2] = (t_xyz){0.5f * plr->width,
		-0.5f * plr->height, 0.0f, 1.0f};
	plr->tri[0].normal = (t_xyz){0.0f, 0.0f, -1.0f, 0.0f};
	plr->tri[1].normal = (t_xyz){0.0f, 0.0f, -1.0f, 0.0f};
}

void	init_player(t_player *plr)
{
	plr->dir.x = 0.0f;
	plr->dir.y = 1.0f;
	plr->time = SDL_GetTicks();
	plr->message_time = 0;
	plr->cur_sector = 0;
	plr->pos = (t_xyz){0.8f, 3.5f, 2.87f, 1.0f};
	plr->look_dir = (t_xyz){0.0f, 0.0f, 1.0f, 1.0f};
	plr->up = (t_xyz){0.0f, 1.0f, 0.0f, 1.0f};
	plr->target = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	plr->pitch = 0.0f;
	plr->yaw = 0.0f;
	plr->roll = 0.0f;
	plr->height = 1.5f;
	plr->width = 0.3f;
	plr->power_points = 2.0f;
	plr->fuel_points = 100.0f;
	plr->active_inv = -1;
	plr->active_wep = 0;
	plr->inventory[0] = 0;
	plr->inventory[1] = 0;
	plr->inventory[2] = 0;
	plr->inventory[3] = 0;
	plr->steps = 0.0f;
	plr->plot_state = no_plot;
	plr->wep[0].ammo = 42;
	plr->wep[0].fire_rate = 1.0f;
	plr->wep[0].type = 0;
	plr->speed = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	plr->display_object = 0;
	plr->dead = 0;
	initialize_player_target_triangles(plr);
	init_input_values(&plr->input);
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

void	setup(t_home *home, t_player *plr, t_frame *frame, t_menu *menu)
{
	int				ret;

	(void)plr;
	home->win.width = SCREEN_WIDTH;
	home->win.height = SCREEN_HEIGHT;
	home->chosen_map = NULL;
	home->offset = vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	frame->buffer = (Uint32 *)malloc(sizeof(Uint32)
			* (Uint32)SCREEN_WIDTH * (Uint32)SCREEN_HEIGHT);
	if (!frame->buffer)
		error_output("Memory allocation failed!\n");
	frame->depth_buffer = (float *)malloc(sizeof(float)
			* (SCREEN_WIDTH * SCREEN_HEIGHT + 1));
	if (!frame->depth_buffer)
		error_output("Memory allocation failed!\n");
	else
		printf("Depth buffer allocation succeeded. Address is: %p\n", frame->depth_buffer);
	ret = initialize_rasterization_queues(frame);
	if (ret)
		clean_up(frame);
	home = init_sdl(home, frame, &frame->min_step);
	initialize_audio_to_null(&plr->audio);
	// ret = load_audio(&plr->audio);
	// if (ret)
	// {
	// 	cleanup_audio_source(&plr->audio);
	// 	ft_putendl_fd("Failed to load audio files from source, proceeding without menu music\n", 2);
	// }
	// else
	// 	if (Mix_PlayingMusic() == 0)
	// 		Mix_PlayMusic(plr->audio.music, -1);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	setup_menu(menu, &home->game_state);
}

void	clean_up(t_frame *frame)
{
	if (frame->buffer)
		free(frame->buffer);
	free_queues(frame);
	ft_putendl_fd("Shutting down.", 2);
	exit(EXIT_FAILURE);
}

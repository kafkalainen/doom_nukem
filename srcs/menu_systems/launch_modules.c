/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_modules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:04:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/07/19 18:05:27 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	process_inputs_game_loop(t_player *plr, int *game_state, SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
		{
			*game_state = QUIT;
			break ;
		}
		key_input(plr, e, game_state);
		mouse_handle(plr, e);
	}
}

void	update_objects(t_home *home, t_player *plr, Uint32 delta_time)
{
	Uint32	i;
	// float	distance_squared;
	(void)delta_time;
	// i = 0;
	// while (i < home->nbr_of_projectiles)
	// {
	// 	if (home->projectile_pool[i]->is_active)
	// 	{
	// 		// move_projectile();
	// 		// move each projectile
	// 		// if we hit something, explode and set !is_active
	// 		// apply damage to nearby entities
	// 		// do wall damage sprite on affected wall coordinate
	// 	}
	// 	i++;
	// }
	i = 0;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->state != ENTITY_DEAD) // check to see if entity is dead or not
		{
			if (home->entity_pool[i]->entity_type == 1 || home->entity_pool[i]->entity_type == 2) // entity is an enemy, move to state logics
			{
				determine_angle_between_entity_and_plr(home->entity_pool[i], plr);
				// if (home->entity_pool[i]->take_damage) // determined by projectile while loop
				// 	take_damage_logic(home->entity_pool[i], plr_pos, delta_time);
				// if (!home->entity_pool[i]->is_aggroed)
				// {
				// 	if (check_aggro(plr, home->entity_pool[i], home->sectors[home->entity_pool[i]->sector_idx]))
				// 		printf("we are aggroed\n");
				// 	else
				// entity_move(home->entity_pool[i], home, delta_time);
				// }
				// else
				// {
				// 	if (get_distance_squared(plr->pos, home->entity_pool[i]->pos) > 0.5f)
				// 		entity_chase(home->entity_pool[i], home, delta_time, plr);
				// 	else
				// 		printf("I hit you!\n");
				// }
				// distance_squared = ((plr->pos.x - home->entity_pool[i]->pos.x) * (plr->pos.x - home->entity_pool[i]->pos.x) +
				// 	(plr->pos.y - home->entity_pool[i]->pos.y) * (plr->pos.y - home->entity_pool[i]->pos.y) +
				// 	(plr->pos.z - home->entity_pool[i]->pos.z) * (plr->pos.z - home->entity_pool[i]->pos.z));
				// printf("distance to player: %f\n", distance_squared);
				// if (home->entity_pool[i]->is_aggroed)
				// {
				// 	if (home->entity_pool[i]->state == ENTITY_MOVE && home->entity_pool[i]->sprite_state > ENTITY_SPRITE_MOVE_END) // we are done with moving
				// 	// move or attack
				// }

				// if (home->entity_pool[i]->is_aggroed)
				// 	attack_logic(home->entity_pool[i], plr_pos, delta_time);
				// else
				// idle_logic(home->entity_pool[i], delta_time);
				//if we see plr and !is_aggroed, set is_aggroed and move to attack state || move towards plr

				// if we are not aggroed and we take damage, apply damage and aggro player
			}
		}
		i++;
	}
}

void	update_world(t_player *plr, t_home *home)
{
	Uint32	current_time;
	Uint32	delta_time;

	current_time = SDL_GetTicks();
	delta_time = current_time - plr->time;
	if (delta_time < 1)
		return ;
	plr->time = current_time;
	update_player(plr, home, delta_time);
	// update_objects(home, plr, delta_time);
}

void	launch_game_loop(t_home *home, t_player *plr,
	t_frame *frame, SDL_Event *e)
{
	while (home->game_state == GAME_LOOP)
	{
		fps_timer(&home->t);
		process_inputs_game_loop(plr, &home->game_state, e);
		update_world(plr, home); // TODO: split into process_inputs_game_loop and update_world functions
		update_screen(home, frame, plr);
		render_buffer(frame->buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	free_game_assets(home);
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void	launch_load_menu_loop(t_menu *menu, t_home *home, SDL_Event *e)
{
	int	i;

	menu->option = 0;
	menu->selected = 0;
	menu->start = 0;
	if ((menu->nbr_of_maps - 8) > 0)
		menu->end = 7;
	else
		menu->end = menu->nbr_of_maps - 1;
	while (home->game_state == MAP_MENU && !menu->selected)
	{
		process_inputs_load_menu(&home->game_state, e, menu);
		update_load_menu(menu, e->key.keysym.sym);
		render_buffer(menu->menu_buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	if (menu->selected)
		home->chosen_map = ft_strjoin("map_files/",
				menu->map_names[menu->option]);
	i = 0;
	while (i < menu->nbr_of_maps)
		free(menu->map_names[i++]);
	free(menu->map_names);
	menu->nbr_of_maps = 0;
	menu->option = 0;
}

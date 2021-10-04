/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:31:05 by eparviai          #+#    #+#             */
/*   Updated: 2021/10/04 18:18:53 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static	void	handle_hotkeys(SDL_Keycode keysym, t_action *action)
{
	if (keysym == SDLK_w)
		action->offsetf.y += action->scalarf * 0.8f;
	if (keysym == SDLK_s)
		action->offsetf.y -= action->scalarf * 0.8f;
	if (keysym == SDLK_d)
		action->offsetf.x -= action->scalarf * 0.8f;
	if (keysym == SDLK_a)
		action->offsetf.x += action->scalarf * 0.8f;
	if (keysym == SDLK_f)
	{
		if (action->create_sector == idle)
			action->create_sector = allocate;
	}
	if (keysym == SDLK_g && action->grid == 0)
		action->grid = 1;
	else if (keysym == SDLK_g && action->grid == 1)
		action->grid = 0;
	if (keysym == SDLK_e && action->create_entity == idle)
		action->create_entity = allocate;
	if (keysym == SDLK_l && action->selected_entity >= 0)
		action->link_entity = 1;
	if (keysym == SDLK_u && action->selected_entity >= 0)
		action->unlink_entity = 1;
	if (keysym == SDLK_r && action->delete == idle)
		action->delete = 1;
}

static	void	handle_menukeys1(SDL_Keycode keysym, t_action *action)
{
	action->keysym = keysym;
	if (keysym == SDLK_RCTRL)
		action->prev_keysym = keysym;
	if (keysym == SDLK_BACKSPACE)
	{
		if (action->open_file)
			action->open_file = 0;
		if (action->link_maps)
			action->link_maps = 0;
		action->start = 0;
		action->option = 0;
	}
}

static	void	handle_menukeys2(SDL_Keycode keysym, t_action *action)
{
	if (keysym == SDLK_UP)
	{
		if (action->option > 0 && action->option < action->nbr_of_maps)
			action->option = action->option - 1;
		else if (action->option == 0)
			action->option = (action->nbr_of_maps - 1);
	}
	if (keysym == SDLK_DOWN)
	{
		if (action->option >= 0 && action->option < (action->nbr_of_maps - 1))
			action->option = action->option + 1;
		else if (action->option == (action->nbr_of_maps - 1))
			action->option = 0;
	}
	if (keysym == SDLK_RETURN || keysym == SDLK_KP_ENTER)
	{
		if (action->open_file)
			action->open_file = 2;
		if (action->link_maps)
			action->link_maps = 2;
	}
}

void	editor_keyboard(SDL_Keycode keysym, t_action *action)
{
	if (action->input_active)
	{
		if (keysym == SDLK_RETURN)
		{
			action->input_active = 0;
			action->keysym = -1;
		}
		else
			action->keysym = keysym;
		return ;
	}
	else if (action->link_maps || action->open_file)
	{
		handle_menukeys1(keysym, action);
		handle_menukeys2(keysym, action);
	}
	else
		handle_hotkeys(keysym, action);
}

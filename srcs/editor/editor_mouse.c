/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <eparviai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:31:05 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/15 18:32:33 by eparviai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static	void	handle_mb_down1(SDL_Event *e, t_action *action,
	t_mouse_data *mouse_data)
{
	if (e->button.button == SDL_BUTTON_LEFT)
		mouse_data->i_mbleft = 1;
	if (e->button.button == SDL_BUTTON_RIGHT)
		mouse_data->i_mbright = 1;
	if ((e->button.button == SDL_BUTTON_LEFT
			&& action->create_entity == allocate))
		action->create_entity = user_input;
	if (e->button.button == SDL_BUTTON_RIGHT
		&& action->create_entity == allocate)
		action->create_entity = idle;
	if (e->button.button == SDL_BUTTON_LEFT
		&& action->convert_to_portal == allocate)
		action->convert_to_portal = user_input;
	if (e->button.button == SDL_BUTTON_RIGHT
		&& action->convert_to_portal == allocate)
		action->convert_to_portal = idle;
	if ((e->button.button == SDL_BUTTON_LEFT
			&& action->selected_entity >= 0 && action->link_entity == allocate))
	{
		action->prev_entity = action->selected_entity;
		action->link_entity = user_input;
	}
}

static	void	handle_mb_down2(SDL_Event *e, t_action *action)
{
	if (e->button.button == SDL_BUTTON_RIGHT && action->link_entity == allocate)
	{
		action->prev_entity = -1;
		action->link_entity = idle;
	}
	if (e->button.button == SDL_BUTTON_LEFT
		&& action->assign_player_start == allocate)
		action->assign_player_start = user_input;
	if (e->button.button == SDL_BUTTON_RIGHT
		&& action->assign_player_start == allocate)
		action->assign_player_start = idle;
	if (e->button.button == SDL_BUTTON_LEFT
		&& action->assign_end_sector == allocate)
		action->assign_end_sector = user_input;
	if (e->button.button == SDL_BUTTON_RIGHT
		&& action->assign_end_sector == allocate)
		action->assign_end_sector = idle;
}

static	void	handle_mb_up(SDL_Event *e, t_mouse_data *mouse_data)
{
	if (e->button.button == SDL_BUTTON_LEFT)
		mouse_data->i_mbleft = 0;
	if (e->button.button == SDL_BUTTON_RIGHT)
		mouse_data->i_mbright = 0;
}

void	editor_mouse(t_mouse_data *mouse_data, SDL_Event *e,
	t_action *action, t_buffer *buffer)
{
	t_screen_xy	pos;

	mouse_data->x = e->motion.x;
	mouse_data->y = e->motion.y;
	SDL_GetMouseState(&pos.x, &pos.y);
	action->mouse_pos = get_ndc(buffer, pos);
	action->world_pos = ndc_to_world(action->mouse_pos, action->offsetf,
			action->scalarf);
	if (e->type == SDL_MOUSEWHEEL && e->wheel.y > 0
		&& action->scalarf < ZOOM_IN_MAX)
		mouse_zoom(action, 1);
	if (e->type == SDL_MOUSEWHEEL && e->wheel.y < 0
		&& action->scalarf > ZOOM_OUT_MAX)
		mouse_zoom(action, 0);
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		handle_mb_down1(e, action, mouse_data);
		handle_mb_down2(e, action);
	}
	if (e->type == SDL_MOUSEBUTTONUP)
		handle_mb_up(e, mouse_data);
}

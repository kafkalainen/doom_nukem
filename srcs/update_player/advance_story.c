/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_story.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:59:56 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/08 08:37:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	free_story(char ***array, Uint32 nb_of_strings)
{
	Uint32	i;

	i = nb_of_strings;
	while (i--)
	{
		free(*(*array + i));
		*(*array + i) = NULL;
	}
	free(*array);
	*array = NULL;
}

/*
**	Here we can also implement player action that
**	affects story items that are played
**	based on world interaction.
*/
t_bool	evolve_story(t_player *plr, t_sector *sector, t_sector *msg_sector)
{
	if (plr->message_time > plr->time)
		return (false);
	else
	{
		if (plr->plot_state == sector_plot)
		{
			if (msg_sector->cur_msg < msg_sector->nb_of_msgs)
				msg_sector->cur_msg++;
			if (plr->cur_sector != plr->msg_sector)
				msg_sector->cur_msg = msg_sector->nb_of_msgs;
			plr->plot_state = no_plot;
		}
		if (plr->plot_state == no_plot && sector->nb_of_msgs
			&& sector->cur_msg < sector->nb_of_msgs)
		{
			plr->plot_state = sector_plot;
			plr->msg_sector = plr->cur_sector;
			plr->message_time = plr->time
				+ ft_strlen(sector->story[sector->cur_msg])
				* 50 + 5000;
			play_sound(plr->audio.rahikainen_ramble[(int)plr->time % 3], 30);
		}
		return (true);
	}
}

void	write_message(t_buffer *buffer, t_player *plr, char *msg,
		t_plx_modifier *mod)
{
	float			percentage;

	percentage = 1.0f - ((plr->message_time - plr->time - 5000) * 0.0002f);
	mod->len = (size_t)(ft_strlen(msg) * percentage);
	ft_str_pxl(buffer,vec2(100, SCREEN_HEIGHT - 30),
		msg, *mod);
}

void	draw_plot_state(t_home *home, t_buffer *buffer, t_player *plr)
{
	Uint32			cur_story;
	t_plx_modifier	mod;

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	cur_story = home->sectors[plr->msg_sector]->cur_msg;
	if (plr->plot_state == sector_plot && plr->message_time > plr->time)
		write_message(buffer, plr,
			home->sectors[plr->msg_sector]->story[cur_story], &mod);
	if (plr->plot_state != sector_plot
		&& plr->message_time > (plr->time + 3000))
		write_message(buffer, plr, home->story[plr->plot_state], &mod);
	else if (plr->plot_state != sector_plot && plr->message_time > plr->time)
	{
		mod.len = (size_t)(ft_strlen(home->story[plr->plot_state]));
		ft_str_pxl(buffer, vec2(100, SCREEN_HEIGHT - 30),
			home->story[plr->plot_state], mod);
	}
}

void	end_level(t_home *home, t_player *plr)
{
	if (plr->cur_sector == home->end_sector)
	{
		if (home->linked_map)
			home->game_state = GAME_CONTINUE;
		else
			home->game_state = MAIN_MENU;
	}
	if (plr->power_points <= 0 && plr->dead == 0)
	{
		play_sound(plr->audio.rahikainen_damage[1], 30);
		plr->dead = 1;
	}
}

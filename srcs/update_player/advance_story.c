/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_story.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:59:56 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/02 16:00:37 by jnivala          ###   ########.fr       */
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

void	evolve_story(t_player *plr, t_sector *sector, t_sector *msg_sector,
		Uint32 delta_time)
{
	if (plr->msg_time > 0)
		plr->msg_time -= delta_time;
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
			plr->msg_time = ft_strlen(sector->story[sector->cur_msg]) * 150;
			plr->total_msg_time = plr->msg_time;
			play_sound_and_fadeout(
				plr->audio.rahikainen_ramble[(int)plr->time % 3], 15,
				plr->total_msg_time);
		}
	}
}

void	write_message(t_buffer *buffer, t_player *plr, char *msg,
		t_plx_modifier *mod)
{
	float			percentage;
	t_xy			offset;

	percentage = 1.0f - plr->msg_time / (float)plr->total_msg_time;
	mod->len = (size_t)(ft_strlen(msg) * percentage);
	if (mod->len > 90)
		mod->len = 90;
	if (mod->len > 0)
	{
		offset.x = center_text_x_axis(0, buffer->width, mod->size, mod->len);
		offset.y = SCREEN_HEIGHT - 100;
		ft_str_pxl(buffer, offset, msg, *mod);
	}
}

void	draw_plot_state(t_home *home, t_buffer *buffer, t_player *plr)
{
	Uint32			cur_story;
	t_plx_modifier	mod;

	mod.colour = 0xFFFFFFFF;
	mod.size = TEXT_SIZE;
	cur_story = home->sectors[plr->msg_sector]->cur_msg;
	if (plr->plot_state == sector_plot && plr->msg_time > 0)
		write_message(buffer, plr,
			home->sectors[plr->msg_sector]->story[cur_story], &mod);
}

void	end_level(t_home *home, t_player *plr)
{
	if (plr->cur_sector == home->end_sector
		&& !home->sectors[home->end_sector]->nb_of_msgs)
		end_logic(plr, home);
	else if (plr->cur_sector == home->end_sector
		&& home->sectors[home->end_sector]->nb_of_msgs)
		initialize_cutscene(home->sectors[home->end_sector], plr, end_cutscene);
	if (plr->power_points <= 0 && plr->dead == 0)
	{
		play_sound(plr->audio.rahikainen_die, 30);
		plr->dead = 1;
	}
}

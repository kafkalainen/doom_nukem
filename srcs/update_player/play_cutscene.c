/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_cutscene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 08:29:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 21:29:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	end_logic(t_player *plr, t_home *home)
{
	plr->plot_state = no_plot;
	if (home->linked_map)
		home->game_state = GAME_CONTINUE;
	else
		home->game_state = MAIN_MENU;
}

void	update_cutscene(t_player *plr, t_home *home, Uint32 t)
{
	t_sector	*temp;

	temp = NULL;
	if (plr->plot_state == start_cutscene)
		temp = home->sectors[plr->start_sector];
	if (plr->plot_state == end_cutscene)
		temp = home->sectors[home->end_sector];
	if (plr->cutscene > 0 && plr->input.skip == false)
		plr->cutscene -= t;
	else
	{
		temp->cur_msg++;
		if (temp->cur_msg <= temp->nb_of_msgs)
			initialize_cutscene(temp, plr, plr->plot_state);
		else
		{
			if (plr->plot_state == start_cutscene)
				plr->plot_state = no_plot;
			else if (plr->plot_state == end_cutscene)
				end_logic(plr, home);
		}
	}
}

void	initialize_cutscene(t_sector *sector, t_player *plr, int type)
{
	if (sector->nb_of_msgs > 0 && sector->cur_msg <= sector->nb_of_msgs)
	{
		if (plr->input.skip == true)
		{
			sector->cur_msg = sector->nb_of_msgs;
			plr->cutscene_total = 0;
			plr->input.skip = false;
		}
		else
		{
			plr->plot_state = type;
			if (sector->cur_msg == sector->nb_of_msgs)
				plr->cutscene = 7000;
			else
				plr->cutscene = ft_strlen(sector->story[sector->cur_msg]) * 99;
			plr->cutscene_total = plr->cutscene;
			plr->ending_played = false;
			if (sector->cur_msg != 0 && sector->cur_msg != sector->nb_of_msgs)
				play_sound_and_fadeout(plr->audio.typing, 30,
					plr->cutscene_total);
		}
	}
}

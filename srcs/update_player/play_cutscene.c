/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_cutscene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 08:29:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 15:12:47 by jnivala          ###   ########.fr       */
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
	if (plr->cutscene > 0)
		plr->cutscene -= t;
	else
	{
		temp->cur_msg++;
		if (temp->cur_msg < temp->nb_of_msgs)
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

void	initialize_cutscene(t_sector *cutscene_sector, t_player *plr, int type)
{
	if (cutscene_sector->nb_of_msgs > 0
		&& cutscene_sector->cur_msg < cutscene_sector->nb_of_msgs)
	{
		plr->plot_state = type;
		plr->cutscene_total = ft_strlen(
				cutscene_sector->story[cutscene_sector->cur_msg]) * 250;
		plr->cutscene = plr->cutscene_total;
		plr->ending_played = false;
		play_sound_and_fadeout(plr->audio.typing, 30, plr->cutscene_total);
	}
}

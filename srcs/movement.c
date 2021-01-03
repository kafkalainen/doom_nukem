/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:08:50 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/24 18:08:50 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h"

void		movement(t_player *plr)
{
	double		delta_time;
	clock_t		ctime;

	ctime = clock();
	delta_time = ((ctime - plr->time) / (double)CLOCKS_PER_SEC);
	if (delta_time < 0.0166667)
		return (1);
	plr->time = ctime;
	if (plr->input.down == 1)
		plr->pos = vec2_dec(plr->pos, vec2_mul(plr->dir, 10 * delta_time));
	else if (plr->input.up == 1)
		plr->pos = vec2_add(plr->pos, vec2_mul(plr->dir, 10 * delta_time));
	if (plr->input.right == 1)
		plr->pos = vec2_add(plr->pos, vec2_mul(vec2_rot(plr->dir, 90 * DEG_TO_RAD), 10 * delta_time));
	if (plr->input.left == 1)
		plr->pos = vec2_dec(plr->pos, vec2_mul(vec2_rot(plr->dir, 90 * DEG_TO_RAD), 10 * delta_time));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:17:58 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 10:19:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:55:55 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 10:09:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	generate_window(t_wall *portal, t_uint *nb_of_walls)
{
	t_point_data	left;
	t_point_data	right;
	t_wall			*new_window;

	if (!portal->is_window)
		return ;
	left.x = portal->top.p[1].x;
	right.x = portal->top.p[2].x;
	left.y = portal->top.p[1].z;
	right.y = portal->top.p[2].z;
	left.ceiling = portal->top.p[1].y;
	right.ceiling = portal->top.p[2].y;
	left.ground = portal->bot.p[0].y;
	right.ground = portal->bot.p[2].y;
	if (portal->is_window == 1)
		left.idx = -small_window;
	else if (portal->is_window == 2)
		left.idx = -large_window;
	portal->is_closed = true;
	new_window = new_point(&left, &right);
	if (!new_window)
		error_output("ERROR: Couldn't create window.");
	add_to_middle(&portal, new_window);
	*nb_of_walls += 1;
}

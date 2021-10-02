/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_valid_draw_range.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 11:26:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/02 11:27:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_for_valid_draw_range(t_steps *step)
{
	if (step->start.x < 0 || step->start.y > SCREEN_HEIGHT - 1
		|| step->start.y < 0 || step->end.x > SCREEN_WIDTH - 1
		|| step->start.x >= step->end.x)
		return (false);
	else
		return (true);
}

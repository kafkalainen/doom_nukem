/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_hull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:04:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 09:54:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	show_hull(t_triangle *viewed_tri)
{
	if (viewed_tri->hull)
	{
		initialize_lumels(&viewed_tri->lu[0], &viewed_tri->lu[1],
			&viewed_tri->lu[2], 0.275f);
		if (viewed_tri->type == -small_window)
			viewed_tri->type = -hull_small_window;
		else if (viewed_tri->type == -large_window)
			viewed_tri->type = -hull_large_window;
		else
			viewed_tri->type = -wall7;
	}
}

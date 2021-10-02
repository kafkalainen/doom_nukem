/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inflate_idx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:34:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/02 13:46:40 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_inflate_idx(int idx)
{
	if (idx > 20999)
		idx = LARGE_WINDOW_INDEX;
	else if (idx > 17999)
		idx = SMALL_WINDOW_INDEX;
	else if (idx > 14999)
		idx = SECRET_INDEX;
	else if (idx > 11999)
		idx = MILITARY_INDEX;
	else if (idx > 8999)
		idx = ENGINEERING_INDEX;
	else if (idx > 5999)
		idx = CLEANING_INDEX;
	else if (idx > 2999)
		idx = DOOR_INDEX;
	else
		idx = 0;
	return (idx);
}

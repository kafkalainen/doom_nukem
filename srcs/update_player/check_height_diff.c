/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_height_diff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:01:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/05 13:15:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	We need to linearally interpolate at which point player is
**	crossing to another sector.
**
*/

int	check_height_diff(float *z, t_point *to)
{
	if (*z - to->ground < -10)
		return (1);
	else if (to->ceiling - to->ground < 3)
		return (1);
	else
		return (0);
}

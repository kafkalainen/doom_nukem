/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:09:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/21 20:34:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_floor(int floor_colour)
{
	if (floor_colour == -1)
		return (darkolivegreen);
	else if (floor_colour == -2)
		return (steelblue);
	else if (floor_colour == -3)
		return (darkturquoise);
	else if (floor_colour == -4)
		return (snow);
	else if (floor_colour == -5)
		return (dimgray);
	else
		return (green);
}

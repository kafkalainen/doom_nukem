/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:41:13 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/21 16:45:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	ship_part(int type)
{
	if (type == -door)
		return (false);
	else if (type == -bullet_decal)
		return (false);
	else if (type == -power_station_depleted || type == -power_station_ready)
		return (false);
	else if (type == -button_on || type == -button_off)
		return (false);
	else
		return (true);
}

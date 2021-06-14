/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_negative.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:04:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/14 12:50:06 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	is_negative(float z)
{
	if (z < 0)
		return (1);
	else
		return (0);
}

int	give_sign(float number)
{
	if (number < 0)
		return (-1);
	else if (number == 0)
		return (0);
	else
		return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 10:00:58 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 11:34:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	other_dir(int dir)
{
	if (dir == lower)
		return (upper);
	else if (dir == upper)
		return (lower);
	else
		return (0);
}

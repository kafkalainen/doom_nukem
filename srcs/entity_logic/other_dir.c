/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 10:00:58 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/04 10:01:54 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	other_dir(Uint32 dir)
{
	if (dir == lower)
		return (upper);
	else if (dir == upper)
		return (lower);
	else
		return (0);
}

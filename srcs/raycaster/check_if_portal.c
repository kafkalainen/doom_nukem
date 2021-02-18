/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_portal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:38:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/09 14:55:40 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int		check_if_portal(t_point *p0, t_frame *frame)
{
	if (p0->idx >= 0)
		return (TRUE);
	else
		return (FALSE);
}

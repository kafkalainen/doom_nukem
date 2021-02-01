/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:49:54 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/01 12:12:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_point	*back_to_start(t_point *x0, t_home *home, int index)
{
	return ((x0->next == NULL) ? home->sectors[index]->points : x0->next);
}

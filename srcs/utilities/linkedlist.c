/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:49:54 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/29 09:33:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_polygon	*back_to_start(t_polygon *x0, t_home *home, int index)
{
	return ((x0->next == NULL) ? home->sectors[index]->polygons : x0->next);
}

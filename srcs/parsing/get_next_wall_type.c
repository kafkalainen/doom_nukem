/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:10:29 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/24 17:12:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	get_next_wall_type(t_wall *portal, int *next)
{
	if (portal->next->top.type < 0 && portal->next->top.type != -door)
		*next = portal->next->top.type;
	else
		*next = -2;
}

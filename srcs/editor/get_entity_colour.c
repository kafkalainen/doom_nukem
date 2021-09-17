/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entity_colour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:12:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/17 11:07:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_uint	get_entity_colour(t_entity_list *entity, int selected_entity)
{
	if (entity->entity_idx == selected_entity)
		return (get_color(gold));
	else
		return (get_color(dimgray));
}

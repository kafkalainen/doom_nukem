/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_entity_link_booleans.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:37:46 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 13:37:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	link_allowed(t_entity_list *from, t_entity_list *to)
{
	if ((from->entity_type == light_button && to->entity_type == lamp)
		|| (from->entity_type == lamp && to->entity_type == light_button))
		return (true);
	return (false);
}

t_bool	is_linkable_entity(int entity_type)
{
	if (entity_type == light_button || entity_type == lamp)
		return (true);
	else
		return (false);
}

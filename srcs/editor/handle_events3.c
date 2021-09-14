/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:24:38 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/11 14:34:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_last_written_character(unsigned char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	if (i == 0)
		return ('\n');
	return ((int)string[i - 1]);
}

int	write_story_ruleset(int *keysym, unsigned char **string)
{
	int	c;

	if (*keysym == '#')
		return (false);
	if (*keysym == SDLK_TAB)
	{
		if (*string == NULL)
			return (false);
		c = get_last_written_character(*string);
		if (c == '\n')
			return (false);
		*keysym = '\n';
		return (true);
	}
	if (!ft_isprint(*keysym))
		return (false);
	return (true);
}

void	unlink_selected_entity(t_entity_list **list, int entity_idx,
		int *unlink_state)
{
	t_entity_list	*temp;

	temp = *list;
	while (temp != NULL && temp->entity_idx != entity_idx)
		temp = temp->next;
	if (temp != NULL)
		temp->is_linked = 0;
	*unlink_state = 0;
}

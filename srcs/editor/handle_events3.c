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

unsigned char	*delete_char_from_string(unsigned char **string)
{
	unsigned char	*temp;
	int				size;

	size = ft_strlen((const char *)*string);
	if (size > 1)
	{
		temp = (unsigned char *)ft_strndup((const char *)*string, size - 1);
		free(*string);
	}
	else
	{
		if (*string != NULL)
			free(*string);
		return (NULL);
	}
	return (temp);
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

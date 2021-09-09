/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:24:38 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/09 11:11:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// DEBUGGING
// void	new_check_event(t_editor *editor)
// {
// 	t_mouse_data	mdata;

// 	mdata = editor->mouse_data;
// 	if (mdata.x > 300 && mdata.x < editor->buffer.width && mdata.y > 0
//	&& mdata.y < editor->buffer.height)
// 	{

// 	}
// 	if (editor->action.link_entity == 2
//	&& editor->action.prev_entity != -1 && editor->temp_entity != NULL)
// 	{
// 		link_entities(&editor->entity_list, mdata,
//			editor->action.prev_entity);
// 		editor->action.link_entity = 0;
// 	}
// }
unsigned char	*delete_char_from_string(unsigned char **string)
{
	unsigned char	*temp;
	int				size;

	size = ft_strlen((const char *)*string);
	if (size > 0)
	{
		temp = (unsigned char *)ft_strndup((const char *)*string, size - 1);
		free(*string);
	}
	else
		return (NULL);
	return (temp);
}

void	read_input_string(unsigned char **string, t_action *action)
{
	char	c;

	if (action->keysym == SDLK_BACKSPACE && *string != NULL)
		*string = delete_char_from_string(string);
	if (ft_isspace(action->keysym)
		|| (*string != NULL
			&& ft_strlen((const char *)*string) > MAX_FILE_NAME_LENGTH
			&& action->save_file))
	{
		action->keysym = -1;
		return ;
	}
	if (action->input_active && ft_isprint(action->keysym))
	{
		c = action->keysym;
		if (*string == NULL)
			*string = (unsigned char *)ft_strdup((const char *)&c);
		else
		{
			*string = (unsigned char *)ft_strjoin_freeable((char *)*string,
					(char *)&c, 1, 0);
		}
	}
	action->keysym = -1;
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

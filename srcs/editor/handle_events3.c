/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:24:38 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/10 19:23:53 by rzukale          ###   ########.fr       */
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

int	save_mapname_ruleset(int keysym, unsigned char **string)
{
	if (ft_isspace(keysym))
		return (false);
	if (!ft_isalnum(keysym))
		return (false);
	if (*string != NULL && ft_strlen((const char *)*string) > MAX_FILE_NAME_LENGTH)
		return (false);
	return (true);
}

int	edit_wall_ruleset(int *keysym, unsigned char **string)
{
	if (*string != NULL && ft_strlen((const char *)*string) > 2)
		return (false);
	if (*keysym == SDLK_SLASH || *keysym == SDLK_MINUS)
	{
		*keysym = '-';
		printf("vittu\n");
		return (true);
	}
	if (!ft_isdigit(*keysym))
		return (false);
	return (true);
}

void	read_input_string(unsigned char **string, t_action *action)
{
	char	c;

	if (action->keysym == SDLK_BACKSPACE && *string != NULL)
		*string = delete_char_from_string(string);
	if ((action->save_file && !save_mapname_ruleset(action->keysym, string)) ||
		(action->edit_wall && !edit_wall_ruleset(&action->keysym, string)))
	{
		action->keysym = -1;
		return ;
	}
	// ruleset for plot strings
	if (action->input_active)
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

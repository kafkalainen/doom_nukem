/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <eparviai@student.hive.fi>         +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:24:38 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/11 14:34:53 by eparviai          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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

int	save_mapname_ruleset(int keysym, unsigned char **string)
{
	if (ft_isspace(keysym))
		return (false);
	if (!ft_isalnum(keysym))
		return (false);
	if (*string != NULL && ft_strlen((const char *)*string)
		 > MAX_FILE_NAME_LENGTH)
		return (false);
	return (true);
}

int	int_string_ruleset(int *keysym, unsigned char **string)
{
	if (*string != NULL && ft_strlen((const char *)*string) > 2)
		return (false);
	if (*keysym == SDLK_SLASH || *keysym == SDLK_MINUS)
	{
		*keysym = '-';
		return (true);
	}
	if (!ft_isdigit(*keysym))
		return (false);
	return (true);
}

static int	verify_action(unsigned char **string, t_action *action)
{
	if ((action->save_file && !save_mapname_ruleset(action->keysym, string))
		|| ((action->edit_ceiling_height
				|| action->edit_floor_height || action->set_light_intensity)
			&& !int_string_ruleset(&action->keysym, string))
		|| (action->write_sector_story
			&& !write_story_ruleset(&action->keysym, string)))
	{
		action->keysym = -1;
		return (1);
	}
	return (0);
}

void	read_input_string(unsigned char **string, t_action *action)
{
	char	c[2];

	if (action->keysym == SDLK_BACKSPACE && *string != NULL)
		*string = delete_char_from_string(string);
	if (verify_action(string, action))
		return ;
	if (action->input_active)
	{
		c[0] = action->keysym;
		c[1] = '\0';
		if (*string == NULL)
			*string = (unsigned char *)ft_strdup((const char *)c);
		else
		{
			*string = (unsigned char *)ft_strjoin_freeable((char *)*string,
					(char *)c, 1, 0);
		}
	}
	action->keysym = -1;
}
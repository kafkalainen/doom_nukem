/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:24:38 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/15 15:39:41 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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
				|| action->edit_floor_height || action->set_light_intensity
				|| action->set_all_sector_ceiling_heights
				|| action->set_all_sector_floor_heights)
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

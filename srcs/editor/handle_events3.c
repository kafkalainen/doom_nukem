/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:24:38 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/15 10:55:35 by jnivala          ###   ########.fr       */
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

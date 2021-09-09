/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   porting_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:44:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/09 12:33:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

char	*ft_strjoin_freeable(char *s1, char *s2, int free_one, int free_two)
{
	char	*concat_str;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concat_str = (char *)malloc(sizeof(*concat_str) * (s1_len + s2_len + 1));
	if (concat_str != NULL)
	{
		ft_strcpy(concat_str, s1);
		ft_strcat(concat_str, s2);
	}
	if (free_one)
		free(s1);
	if (free_two)
		free(s2);
	return (concat_str);
}

int	get_nbr_of_sectors(t_editor_sector **sectors)
{
	int				len;
	t_editor_sector	*temp;

	len = 0;
	temp = *sectors;
	if (*sectors == NULL)
		return (0);
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

int	check_if_linked(unsigned char *linked_map)
{
	if (linked_map)
		return (1);
	return (0);
}

int	get_nbr_of_lines(unsigned char *plot)
{
	int				i;
	int				lines;

	i = 0;
	lines = 1;
	while (plot[i] != '\0')
	{
		if (plot[i] == '\n')
			lines++;
		i++;
	}
	return (lines);
}

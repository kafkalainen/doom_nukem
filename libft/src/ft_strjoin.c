/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 14:17:40 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/02 13:00:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char		*concat_str;
	size_t		s1_len;
	size_t		s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concat_str = (char*)malloc(sizeof(*concat_str) * (s1_len + s2_len + 1));
	if (concat_str != NULL)
	{
		ft_strcpy(concat_str, s1);
		ft_strcat(concat_str, s2);
	}
	return (concat_str);
}

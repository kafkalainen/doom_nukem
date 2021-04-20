/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 08:36:43 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/01 16:46:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdlib.h>

char	**ft_strarrnew(size_t arr_len, char const *str)
{
	size_t		i;
	char		**new_arr;

	i = 0;
	new_arr = (char**)malloc(sizeof(*new_arr) * (arr_len + 1));
	if (new_arr == NULL || str == NULL)
		return (NULL);
	while (i < arr_len)
	{
		new_arr[i] = ft_strdup(str);
		if (new_arr[i] == NULL)
		{
			while (i)
			{
				ft_strdel(&new_arr[i]);
				i--;
			}
			free(new_arr);
			new_arr = NULL;
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

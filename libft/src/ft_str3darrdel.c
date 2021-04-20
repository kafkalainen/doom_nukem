/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3darrdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:47:41 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/20 15:01:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdlib.h>

char	***ft_str3darrdel(char ****a3d, size_t z, size_t y)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (*a3d != NULL)
	{
		while (i < z)
		{
			j = 0;
			while (j < y)
			{
				ft_strdel(&(*(*(*(a3d) + i) + j)));
				j++;
			}
			free(*(*(a3d) + i));
			*(*(a3d) + i) = NULL;
			i++;
		}
		free(*a3d);
		*a3d = NULL;
	}
	return (NULL);
}

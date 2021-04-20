/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 10:33:38 by jnivala           #+#    #+#             */
/*   Updated: 2020/10/30 17:05:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdlib.h>

char	**ft_strarrdel(char ***as, size_t y)
{
	size_t		i;

	i = 0;
	if (as != NULL)
	{
		while (i < y)
		{
			ft_strdel((*(as) + i));
			i++;
		}
		free(*as);
		*as = NULL;
	}
	return (NULL);
}

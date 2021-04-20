/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 11:35:01 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 19:01:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (size != 0)
	{
		mem = (void *)malloc(sizeof(*mem) * size);
		if (mem != NULL)
		{
			ft_bzero(mem, size);
			return (mem);
		}
	}
	return (NULL);
}

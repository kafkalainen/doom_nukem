/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 08:40:25 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/17 15:18:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void		*ft_memset(void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*temp;

	i = 0;
	temp = (unsigned char*)s;
	while (i < n)
	{
		temp[i] = (unsigned char)c;
		i++;
	}
	return ((void*)temp);
}

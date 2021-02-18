/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:13:09 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/18 16:17:58 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count && (dest || src))
	{
		*((unsigned char*)dest + i) = *((unsigned char*)src + i);
		i++;
	}
	return (dest);
}

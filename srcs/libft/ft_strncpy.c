/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:15:56 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/26 10:59:51 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

char	*ft_strncpy(char *dest, const char *src, size_t count)
{
	size_t i;

	i = 0;
	while (src[i] != '\0' && i < count)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < count)
		dest[i++] = '\0';
	return (dest);
}

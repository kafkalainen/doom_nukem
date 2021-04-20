/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 09:53:28 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/01 14:15:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		src_len;
	size_t		dst_len;
	size_t		space_left;

	i = 0;
	dst_len = 0;
	src_len = ft_strlen(src);
	while (dst_len < size && dst[dst_len] != '\0')
		dst_len++;
	space_left = size - dst_len - 1;
	if (dst_len == size)
		return (src_len + size);
	while (space_left && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
		space_left--;
	}
	if (dst[dst_len + i] != '\0')
		dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}

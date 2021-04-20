/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 08:46:48 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/18 12:59:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char		*ft_strrchr(const char *str, int c)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(str);
	while (i < len && str[len - i] != c)
		i++;
	if (str[len - i] == c)
		return (char*)(str + (len - i));
	else
		return (NULL);
}

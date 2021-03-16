/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:07:59 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/09 12:43:47 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int	ft_strncmp(const char *s1, const char *s2, size_t count)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < count)
		i++;
	if (i == count)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

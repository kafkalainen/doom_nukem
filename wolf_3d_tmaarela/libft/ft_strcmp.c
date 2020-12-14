/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:04:27 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 20:34:01 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *)str1;
	p2 = (unsigned char *)str2;
	i = 0;
	while (p1[i] && (p1[i] == p2[i]))
		++i;
	return (p1[i] - p2[i]);
}

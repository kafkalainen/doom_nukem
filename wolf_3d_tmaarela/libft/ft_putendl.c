/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:11:46 by ngontjar          #+#    #+#             */
/*   Updated: 2020/07/26 04:47:51 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putendl(const char *str)
{
	size_t length;

	length = ft_putstr(str);
	write(1, "\n", 1);
	return (length + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnotice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 02:47:29 by ngontjar          #+#    #+#             */
/*   Updated: 2020/07/26 04:49:03 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allows special formatting for debug messages (for example).
** Foreground/Background styling are both optional,
** and the order is not explicit.
*/

size_t	ft_putnotice(const char *str, const char *fg, const char *bg)
{
	size_t length;

	if (fg)
		ft_putstr(fg);
	if (bg)
		ft_putstr(bg);
	length = ft_putstr(str);
	write(1, "\n", 1);
	ft_putstr(TX_NORMAL);
	return (length + 1);
}

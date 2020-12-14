/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:26:20 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 16:56:07 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*pointer;

	if ((pointer = malloc(size)) != NULL)
		return (ft_memset(pointer, 0, size));
	else
		return (NULL);
}

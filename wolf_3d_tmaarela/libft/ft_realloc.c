/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:15:09 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/28 15:30:44 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	char *new;

	new = ft_memcpy(ft_memalloc(new_size), ptr, old_size);
	free(ptr);
	return (new ? new : NULL);
}

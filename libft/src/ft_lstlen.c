/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:25:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 18:43:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_lstlen(t_list **alst)
{
	size_t	len;
	t_list	*temp;

	len = 0;
	temp = *alst;
	if (*alst == NULL)
		return (0);
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

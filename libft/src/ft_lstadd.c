/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 08:49:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 18:43:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (new == NULL)
		return ;
	if (*alst != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
	else
	{
		new->next = NULL;
		*alst = new;
	}
}

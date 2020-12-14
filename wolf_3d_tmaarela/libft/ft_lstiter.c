/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:27:36 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/07 17:47:56 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *link, void (*func)(t_list *link))
{
	while (link != NULL)
	{
		func(link);
		link = link->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:09:57 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/08 21:55:24 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **link, void (*del)(void *, size_t))
{
	del((*link)->content,
		(*link)->content_size);
	free(*link);
	*link = NULL;
}

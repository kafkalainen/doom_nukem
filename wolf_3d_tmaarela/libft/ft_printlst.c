/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 02:47:40 by ngontjar          #+#    #+#             */
/*   Updated: 2020/07/19 02:47:41 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_node(t_list *head)
{
	char *temp;

	ft_putstr("{0x");
	temp = ft_itoa_base((long long)head, 16);
	ft_putstr(temp);
	free(temp);
	ft_putstr(": 0x");
	if (head->content)
	{
		temp = ft_itoa_base((long long)head->content, 16);
		ft_putstr(temp);
		free(temp);
	}
	else
	{
		ft_putstr("null");
	}
	ft_putstr(" (");
	temp = ft_itoa(head->content_size);
	ft_putstr(temp);
	free(temp);
	ft_putstr(" bytes)}");
}

void		ft_printlst(t_list *head)
{
	while (head)
	{
		print_node(head);
		ft_putstr(" ~> ");
		head = head->next;
	}
	ft_putendl("{null}");
}

void		ft_printlst_endl(t_list *head)
{
	while (head)
	{
		print_node(head);
		ft_putstr("\n");
		head = head->next;
	}
	ft_putendl("{null}");
}

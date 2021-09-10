/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pxl_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 09:42:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/10 17:47:36 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_pxl_c	letter_012345(int l, int b, int c)
{
	if (l == '0')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, c, b, b, c, b, c, b, b, c, b,
				c, b, b, c, b, c, b, b, c, c, c, b, b, b, b, b, b}});
	else if (l == '1')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, b, b, b, b, c, b, b, b, b, c,
				b, b, b, b, c, b, b, b, c, c, c, b, b, b, b, b, b}});
	else if (l == '2')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, c, b, b, b, b, c, b, b, c, c,
				c, b, b, c, b, b, b, b, c, c, c, b, b, b, b, b, b}});
	else if (l == '3')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, c, b, b, b, b, c, b, b, b, c,
				c, b, b, b, b, c, b, b, c, c, c, b, b, b, b, b, b}});
	else if (l == '4')
		return ((t_pxl_c){{b, b, b, b, b, b, c, b, c, b, b, c, b, c, b, b, c, c,
				c, b, b, b, b, c, b, b, b, b, c, b, b, b, b, b, b}});
	else
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, c, b, b, c, b, b, b, b, c, c,
				c, b, b, b, b, c, b, b, c, c, c, b, b, b, b, b, b}});
}

static t_pxl_c	letter_6789(int l, int b, int c)
{
	if (l == '6')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, c, b, b, c, b, b, b, b, c, c,
				c, b, b, c, b, c, b, b, c, c, c, b, b, b, b, b, b}});
	else if (l == '7')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, c, b, b, b, b, c, b, b, b, c,
				c, b, b, b, b, c, b, b, b, b, c, b, b, b, b, b, b}});
	else if (l == '8')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, c, b, b, c, b, c, b, b, c, c,
				c, b, b, c, b, c, b, b, c, c, c, b, b, b, b, b, b}});
	else if (l == '9')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, c, b, b, c, b, c, b, b, c, c,
				c, b, b, b, b, c, b, b, b, b, c, b, b, b, b, b, b}});
	else if (l == '+')
		return ((t_pxl_c){{b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, c,
				b, b, b, c, c, c, b, b, b, c, b, b, b, b, b, b, b}});
	else
		return ((t_pxl_c){{b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, c, c,
				c, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b}});
}

static t_pxl_c	letter_special_1(int l, int b, int c)
{
	if (l == '?')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, b, b, b, b, b, c, b, b, b, c,
				b, b, b, b, b, b, b, b, b, c, b, b, b, b, b, b, b}});
	else if (l == '!')
		return ((t_pxl_c){{b, b, b, b, b, b, b, c, b, b, b, b, c, b, b, b, b, c,
				b, b, b, b, b, b, b, b, b, c, b, b, b, b, b, b, b}});
	else if (l == ':')
		return ((t_pxl_c){{b, b, b, b, b, b, b, b, b, b, b, b, c, b, b, b, b, b,
				b, b, b, b, c, b, b, b, b, b, b, b, b, b, b, b, b}});
	else if (l == '\'')
		return ((t_pxl_c){{b, b, b, b, b, b, c, c, b, b, b, b, c, b, b, b, b, b,
				b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b}});
	else
		return ((t_pxl_c){{b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b,
				b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b}});
}

static t_pxl_c	letter_special_2(int l, int b, int c)
{
	if (l == '.')
		return ((t_pxl_c){{b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b,
				b, b, b, b, b, b, b, b, b, b, c, b, b, b, b, b, b}});
	else if (l == ',')
		return ((t_pxl_c){{b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b,
				b, b, b, b, b, c, c, b, b, b, c, b, b, b, b, b, b}});
	else if (l == '(')
		return ((t_pxl_c){{b, b, b, b, b, b, b, b, c, b, b, b, c, b, b, b, b, c,
				b, b, b, b, c, b, b, b, b, b, c, b, b, b, b, b, b}});
	else if (l == ')')
		return ((t_pxl_c){{b, b, b, b, b, b, c, b, b, b, b, b, c, b, b, b, b, c,
				b, b, b, b, c, b, b, b, c, b, b, b, b, b, b, b, b}});
	else if (l == '/')
		return ((t_pxl_c){{b, b, b, b, b, b, b, b, c, b, b, b, c, c, b, b, b, c,
				b, b, b, c, b, b, b, b, c, b, b, b, b, b, b, b, b}});
	else if (l == '-')
		return ((t_pxl_c){{b, b, b, b, b, b, b, b, b, b, b, c, c, c, b, b, c, c,
				c, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b}});
	else
		return ((t_pxl_c){{b, b, b, b, b, b, c, b, c, b, b, b, b, c, b, b, b, c,
				b, b, b, c, b, b, b, b, c, b, c, b, b, b, b, b, b}});
}

t_pxl_c	pxl_numbers(int l, int b, int c)
{
	if (l >= '0' && l <= '5')
		return (letter_012345(l, b, c));
	else if ((l >= '6' && l <= '9') || l == '+' || l == '-')
		return (letter_6789(l, b, c));
	else if (l == ':' || l == '\'' || l == '!' || l == '?' || l == ' ')
		return (letter_special_1(l, b, c));
	else if (l == '.' || l == ',' || l == '(' || l == ')' || l == '%'
		|| l == '/' || l == '-')
		return (letter_special_2(l, b, c));
	else
		return ((t_pxl_c){{b, b, b, b, b, b, b, c, b, b, b, b, c, b, b, b, c, c,
				c, b, b, c, b, c, b, b, c, b, c, b, b, b, b, b, b}});
}

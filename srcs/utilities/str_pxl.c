/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 08:38:48 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/14 11:38:06 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_pxl_c	letter_logic(int c, int letter_colour)
{
	if (c >= 'A' && c <= 'Z')
		return (pxl_alphabet(c, black, letter_colour));
	if (c >= '0' && c <= '9')
		return (pxl_numbers(c, black, letter_colour));
	if (c == ':' || c == '\'' || c == '!' || c == '?' || c == ' '
		|| c == '.' || c == ',' || c == '(' || c == ')' || c == '%')
		return (pxl_numbers(c, black, letter_colour));
	return (pxl_numbers(' ', black, letter_colour));
}

static void		handle_letter(Uint32 *buffer, t_xy coord, int c, t_plx_modifier mods)
{
	t_xy	cur;
	t_pxl_c	letter;
	t_xy	mod;
	int		m;

	cur.y = 0;
	m = mods.size;
	letter = letter_logic(c, mods.colour);
	c = 0;
	while (cur.y < 7)
	{
		cur.x = 0;
		while (cur.x < 5)
		{
			c = letter.c[(int)(cur.x + cur.y * 5)];
			mod.x = cur.x * m + coord.x;
			mod.y = cur.y * m + coord.y;
			draw_square(buffer, mod, c, m);
			cur.x++;
		}
		cur.y++;
	}
}

void			str_pxl(Uint32 *buffer, t_xy coord, char *str, t_plx_modifier mod)
{
	int		c;

	while (*str != '\0')
	{
		c = ft_toupper(*str);
		handle_letter(buffer, coord, c, mod);
		coord.x += 5 * mod.size;
		str++;
	}
}

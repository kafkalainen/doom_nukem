/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:38:29 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/17 12:00:05 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	sub(unsigned char *out, unsigned char *sl, t_scan_helper s)
{
	int	i;

	i = -1;
	while (++i < s.byte_width)
		out[i] = sl[i];
	i = s.byte_width - 1;
	while (++i < s.line_bytes)
		out[i] = sl[i] + out[i - s.byte_width];
}

void	up(unsigned char *out, unsigned char *sl, t_scan_helper s)
{
	int	i;

	i = -1;
	if (s.prev)
	{
		while (++i < s.line_bytes)
			out[i] = sl[i] + s.prev[i];
	}
	else
	{
		while (++i < s.line_bytes)
			out[i] = sl[i];
	}
}

void	avg(unsigned char *out, unsigned char *sl, t_scan_helper s)
{
	int	i;

	i = -1;
	if (s.prev)
	{
		while (++i < s.byte_width)
			out[i] = sl[i] + s.prev[i] / 2;
		i = s.byte_width - 1;
		while (++i < s.line_bytes)
			out[i] = sl[i] + ((out[i - s.byte_width] + s.prev[i]) / 2);
	}
	else
	{
		while (++i < s.byte_width)
			out[i] = sl[i];
		i = s.byte_width - 1;
		while (++i < s.line_bytes)
			out[i] = sl[i] + out[i - s.byte_width] / 2;
	}
}

int	predict(int a, int b, int c)
{
	int	p;
	int	pa;
	int	pb;
	int	pc;

	p = a + b - c;
	if (p > a)
		pa = p - a;
	else
		pa = a - p;
	if (p > b)
		pb = p - b;
	else
		pb = b - p;
	if (p > c)
		pc = p - c;
	else
		pc = c - p;
	if (pa <= pb && pa <= pc)
		return (a);
	else if (pb <= pc)
		return (b);
	else
		return (c);
}

void	paeth(unsigned char *out, unsigned char *sl,
	t_scan_helper s)
{
	int	i;

	i = -1;
	if (s.prev)
	{
		while (++i < s.byte_width)
			out[i] = (unsigned char)(sl[i] + predict(0, s.prev[i], 0));
		i = s.byte_width - 1;
		while (++i < s.line_bytes)
			out[i] = (unsigned char)(sl[i] + predict(out[i - s.byte_width],
						s.prev[i], s.prev[i - s.byte_width]));
	}
	else
	{
		while (++i < s.byte_width)
			out[i] = sl[i];
		i = s.byte_width - 1;
		while (++i < s.line_bytes)
			out[i] = (unsigned char)(sl[i]
					+ predict(out[i - s.byte_width], 0, 0));
	}
}

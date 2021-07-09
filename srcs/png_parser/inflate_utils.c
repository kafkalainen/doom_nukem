/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:01:34 by rzukale           #+#    #+#             */
/*   Updated: 2021/07/09 11:56:02 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

unsigned char	ft_read_bit(unsigned int *bitp,
	const unsigned char *bitstream)
{
	unsigned char	result;

	result = (unsigned char)((bitstream[(*bitp) >> 3] >> ((*bitp) & 0x7)) & 1);
	(*bitp)++;
	return (result);
}

unsigned int	ft_read_bits(unsigned int *bitp,
	const unsigned char *bitstream, unsigned int nbits)
{
	unsigned int	result;
	unsigned int	i;

	result = 0;
	i = 0;
	while (i < nbits)
	{
		result |= ((unsigned int)ft_read_bit(bitp, bitstream)) << i;
		i++;
	}
	return (result);
}

void	get_nbits_replength(unsigned int *nbits, unsigned int code,
	unsigned int *replength)
{
	if (code == 16)
	{
		*replength = 3;
		*nbits = 2;
	}
	else if (code == 17)
	{
		*replength = 3;
		*nbits = 3;
	}
	else if (code == 18)
	{
		*replength = 11;
		*nbits = 7;
	}
}

void	repeat_codes(t_dynamic_helper *d, const unsigned char *in,
	unsigned int *bp)
{
	unsigned int	value;
	unsigned int	nbits;

	nbits = 2;
	get_nbits_replength(&nbits, d->code, &d->replength);
	if (d->code == 16)
		value = d->value;
	else
		value = 0;
	d->replength += ft_read_bits(bp, in, nbits);
	d->n = 0;
	while (d->n < d->replength)
	{
		if (d->i >= (d->hlit + d->hdist))
			error_output("i is larger than the amount of codes\n");
		if (d->i < d->hlit)
			d->bitlen[d->i] = value;
		else
			d->bitlen_dst[d->i - d->hlit] = value;
		d->i++;
		d->n++;
	}
}

void	check_code(t_huffman_helper *s, t_png *png, t_huffman *h)
{
	if (s->code == 256)
		s->done = 1;
	else if (s->code <= 255)
	{
		if (h->pos >= png->inflated_size)
			error_output("reached beyond memory pointer\n");
		png->inflated[h->pos++] = (unsigned char)(s->code);
	}
}

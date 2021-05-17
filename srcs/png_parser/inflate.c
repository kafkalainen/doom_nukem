/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:40:20 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/17 12:13:01 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	ft_inflate_huffman(t_png *png, const unsigned char *in, t_huffman *h)
{
	t_huffman_helper	s;

	s.done = 0;
	while (s.done == 0)
	{
		s.code = ft_huffman_decode_symbol(in, &h->bit_p,
				&h->codetree, png->compressed_size);
		check_code(&s, png, h);
		if (s.code >= FIRST_LENGTH_CODE_INDEX
			&& s.code <= LAST_LENGTH_CODE_INDEX)
		{
			get_length_base_extra(&s.length, &s.numextrabits, s.code);
			if ((h->bit_p >> 3) >= png->compressed_size)
				error_output("bit pointer will jump past memory\n");
			s.length += ft_read_bits(&h->bit_p, in, s.numextrabits);
			s.code_dst = ft_huffman_decode_symbol(in, &h->bit_p,
					&h->codetree_dst, png->compressed_size);
			if (s.code_dst > 29)
				error_output("invalid distance code\n");
			get_dst_base_extra(&s.distance, &s.num_extra_bits_dst, s.code_dst);
			if ((h->bit_p >> 3) >= png->compressed_size)
				error_output("bit pointer will jump past memory\n");
			fill_out(png, &s, h, in);
		}
	}
}

void	ft_inflate_uncompressed(t_png *png, const unsigned char *in,
	unsigned int *bp, unsigned int *pos)
{
	unsigned int	p;
	unsigned int	len;
	unsigned int	nlen;
	unsigned int	n;

	n = 0;
	while (((*bp) & 0x7) != 0)
		(*bp)++;
	p = (*bp) / 8;
	if (p >= (png->compressed_size - 4))
		error_output("zlib size error\n");
	len = in[p] + 256 * in[p + 1];
	p += 2;
	nlen = in[p] + 256 * in[p + 1];
	p += 2;
	if ((len + nlen) != 65535)
		error_output("16-bit nlen should complement len\n");
	if ((*pos) + len <= png->inflated_size)
		error_output("size error\n");
	if ((p + len) > png->compressed_size)
		error_output("size error\n");
	while (n++ < len)
		png->inflated[(*pos)++] = in[p++];
	(*bp) = p * 8;
}

void	go_go_huffman(t_png *png, const unsigned char *in, t_huffman *h)
{
	static unsigned int	fixed_distance_tree[DISTANCE_BUFFER_SIZE] = {
	33, 48, 34, 41, 35, 38, 36, 37, 0, 1, 2, 3, 39, 40, 4, 5, 6, 7, 42, 45, 43,
	44, 8, 9, 10, 11, 46, 47, 12, 13, 14, 15, 49, 56, 50, 53, 51, 52, 16, 17,
	18, 19, 54, 55, 20, 21, 22, 23, 57, 60, 58, 59, 24, 25, 26, 27, 61, 62, 28,
	29, 30, 31, 0, 0 };

	if (h->type == 1)
	{
		init_huffman_tree_codetree_fixed(&h->codetree, NUM_DEFLATE_CODE_SYMBOLS,
			DEFLATE_CODE_BITLEN);
		init_huffman_tree(&h->codetree_dst, (unsigned int *)fixed_distance_tree,
			NUM_DISTANCE_SYMBOLS, DISTANCE_BITLEN);
	}
	else if (h->type == 2)
	{
		init_huffman_tree(&h->codetree, h->codetree_buffer,
			NUM_DEFLATE_CODE_SYMBOLS, DEFLATE_CODE_BITLEN);
		init_huffman_tree(&h->codetree_dst, h->codetree_dst_buffer,
			NUM_DISTANCE_SYMBOLS, DISTANCE_BITLEN);
		init_huffman_tree(&h->code_length_tree, h->code_length_tree_buffer,
			NUM_CODE_LENGTH_CODES, CODE_LENGTH_BITLEN);
		ft_get_tree_inflate_dynamic(h, in, png->compressed_size);
	}
	ft_inflate_huffman(png, in, h);
}

void	ft_inflate_data(t_png *png)
{
	t_huffman	h;
	int			done;

	h.bit_p = 0;
	h.pos = 0;
	done = 0;
	while (done == 0)
	{
		if ((h.bit_p >> 3) > png->compressed_size)
			error_output("bit pointing outside memory pointer\n");
		done = ft_read_bit(&h.bit_p, &png->compressed[2]);
		h.type = ft_read_bit(&h.bit_p, &png->compressed[2])
			| (ft_read_bit(&h.bit_p, &png->compressed[2]) << 1);
		if (h.type == 3)
			error_output("zlib type error\n");
		else if (h.type == 0)
			ft_inflate_uncompressed(png, &png->compressed[2],
				&h.bit_p, &h.pos);
		else
			go_go_huffman(png, &png->compressed[2], &h);
	}
}

void	ft_inflate(t_png *png)
{
	if (png->compressed_size < 2)
		error_output("zlib size error\n");
	if ((png->compressed[0] * 256 + png->compressed[1]) % 31 != 0)
		error_output("FCHECK error\n");
	if ((png->compressed[0] & 15) != 8 || ((png->compressed[0] >> 4) & 15) > 7)
		error_output("zlib compression method error\n");
	ft_inflate_data(png);
}

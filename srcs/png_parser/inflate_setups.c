/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_setups.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:04:19 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/23 11:55:28 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

/*
** the order in which "code length alphabet code lengths" are stored,
** out of this the huffman tree of the dynamic huffman tree lengths is generated
** number of literal/length codes + 257. Unlike the spec, the value 257 is added
** to it here already
** number of distance codes. Unlike the spec, the value 1 is added to it
** here already
** number of code length codes. Unlike the spec, the value 4 is added to
** it here already
*/

void			setup_dynamic_helper(t_dynamic_helper *d,
	const unsigned char *in, unsigned long *bp)
{
	static unsigned int	clcl[NUM_CODE_LENGTH_CODES] = { 16, 17, 18, 0, 8,
		7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

	ft_memset(d->bitlen, 0, sizeof(d->bitlen));
	ft_memset(d->bitlen_dst, 0, sizeof(d->bitlen_dst));
	d->hlit = ft_read_bits(bp, in, 5) + 257;
	d->hdist = ft_read_bits(bp, in, 5) + 1;
	d->hclen = ft_read_bits(bp, in, 4) + 4;
	d->i = -1;
	while (++d->i < NUM_CODE_LENGTH_CODES)
	{
		if (d->i < d->hclen)
			d->codelengthcode[clcl[d->i]] = ft_read_bits(bp, in, 3);
		else
			d->codelengthcode[clcl[d->i]] = 0;
	}
}

/*
** a value of 32767 means uninited,
** a value >= numcodes is an address to another bit,
** a value < numcodes is a code.
** The 2 rows are the 2 possible bit values (0 or 1),
** there are as many columns as codes
*/

void			setup_tree_helper(t_tree_helper *h, const unsigned *bitlen,
	t_huffman_tree *tree)
{
	h->nodefilled = 0;
	h->treepos = 0;
	ft_memset(h->blcount, 0, sizeof(h->blcount));
	ft_memset(h->nextcode, 0, sizeof(h->nextcode));
	h->n = -1;
	while (++h->n < tree->numcodes)
		h->blcount[bitlen[h->n]]++;
	h->n = 0;
	while (++h->n <= tree->maxbitlen)
		h->nextcode[h->n] = (h->nextcode[h->n - 1] + h->blcount[h->n - 1]) << 1;
	h->n = -1;
	while (++h->n < tree->numcodes)
	{
		if (bitlen[h->n] != 0)
			h->tree1d[h->n] = h->nextcode[bitlen[h->n]]++;
	}
	h->n = -1;
	while (++h->n < (tree->numcodes * 2))
		tree->tree2d[h->n] = 32767;
}

/*
** the base lengths represented by codes 257-285
** the extra bits used by codes 257-285 (added to base length)
** part 1: get length base
** part 2: get extra bits and add the value of that to length
*/

void			get_length_base_extra(unsigned long *length,
	unsigned long *num_extra_bits_dst, unsigned int code)
{
	static unsigned int	length_base[29] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15,
		17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227,
		258 };
	static unsigned int	length_extra[29] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0 };

	*length = length_base[code - FIRST_LENGTH_CODE_INDEX];
	*num_extra_bits_dst = length_extra[code - FIRST_LENGTH_CODE_INDEX];
}

/*
** the base backwards distances (the bits of distance codes appear
** after length codes and use their own huffman tree)
** the extra bits of backwards distances (added to base)
** part 4: get extra bits from distance
*/

void			get_dst_base_extra(unsigned int *distance,
	unsigned int *num_extra_bits_dst, unsigned int code_dst)
{
	static unsigned int	distance_base[30] = { 1, 2, 3, 4, 5, 7, 9, 13, 17, 25,
		33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073,
		4097, 6145, 8193, 12289, 16385, 24577 };
	static unsigned int	distance_extra[30] = { 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4,
		4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13 };

	*distance = distance_base[code_dst];
	*num_extra_bits_dst = distance_extra[code_dst];
}

unsigned int	get_deflate_tree_zero(int i)
{
	static unsigned int deflate_code_tree_zero[NUM_DEFLATE_CODE_SYMBOLS] = {
	289, 370, 290, 307, 546, 291, 561, 292, 293, 300, 294, 297, 295, 296, 0, 1,
	2, 3, 298, 299, 4, 5, 6, 7, 301, 304, 302, 303, 8, 9, 10, 11, 305, 306, 12,
	13, 14, 15, 308, 339, 309, 324, 310, 317, 311, 314, 312, 313, 16, 17, 18,
	19, 315, 316, 20, 21, 22, 23, 318, 321, 319, 320, 24, 25, 26, 27, 322, 323,
	28, 29, 30, 31, 325, 332, 326, 329, 327, 328, 32, 33, 34, 35, 330, 331, 36,
	37, 38, 39, 333, 336, 334, 335, 40, 41, 42, 43, 337, 338, 44, 45, 46, 47,
	340, 355, 341, 348, 342, 345, 343, 344, 48, 49, 50, 51, 346, 347, 52, 53,
	54, 55, 349, 352, 350, 351, 56, 57, 58, 59, 353, 354, 60, 61, 62, 63, 356,
	363, 357, 360, 358, 359, 64, 65, 66, 67, 361, 362, 68, 69, 70, 71, 364, 367,
	365, 366, 72, 73, 74, 75, 368, 369, 76, 77, 78, 79, 371, 434, 372, 403, 373,
	388, 374, 381, 375, 378, 376, 377, 80, 81, 82, 83, 379, 380, 84, 85, 86, 87,
	382, 385, 383, 384, 88, 89, 90, 91, 386, 387, 92, 93, 94, 95, 389, 396, 390,
	393, 391, 392, 96, 97, 98, 99, 394, 395, 100, 101, 102, 103, 397, 400, 398,
	399, 104, 105, 106, 107, 401, 402, 108, 109, 110, 111, 404, 419, 405, 412,
	406, 409, 407, 408, 112, 113, 114, 115, 410, 411, 116, 117, 118, 119, 413,
	416, 414, 415, 120, 121, 122, 123, 417, 418, 124, 125, 126, 127, 420, 427,
	421, 424, 422, 423, 128, 129, 130, 131, 425, 426, 132, 133, 134, 135, 428,
	431, 429, 430, 136, 137, 138, 139, 432, 433 };

	return (deflate_code_tree_zero[i]);
}

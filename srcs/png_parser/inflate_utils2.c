/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:13:42 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/20 17:15:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void			fill_nodes(t_tree_helper *h, t_huffman_tree *tree,
	const unsigned int *bitlen)
{
	h->bit = (unsigned char)((h->tree1d[h->n] >>
		(bitlen[h->n] - h->i - 1)) & 1);
	if (h->treepos > tree->numcodes - 2)
		error_output("treeposition mismatch\n");
	if (tree->tree2d[2 * h->treepos + h->bit] == 32767)
	{
		if (h->i + 1 == bitlen[h->n])
		{
			tree->tree2d[2 * h->treepos + h->bit] = h->n;
			h->treepos = 0;
		}
		else
		{
			h->nodefilled++;
			tree->tree2d[2 * h->treepos + h->bit] = h->nodefilled +
				tree->numcodes;
			h->treepos = h->nodefilled;
		}
	}
	else
		h->treepos = tree->tree2d[2 * h->treepos + h->bit] - tree->numcodes;
}

unsigned int	ft_huffman_decode_symbol(const unsigned char *in,
	unsigned int *bp, t_huffman_tree *codetree, unsigned int inlength)
{
	unsigned int	treepos;
	unsigned int	ct;
	unsigned char	bit;

	treepos = 0;
	ct = 0;
	while (1)
	{
		if (((*bp) & 0x07) == 0 && ((*bp) >> 3) > inlength)
			error_output("end of input memory reached without endcode\n");
		bit = ft_read_bit(bp, in);
		ct = codetree->tree2d[(treepos << 1) | bit];
		if (ct < codetree->numcodes)
			return (ct);
		treepos = ct - codetree->numcodes;
		if (treepos >= codetree->numcodes)
			error_output("invalid\n");
	}
}

void			dynamic_code_cycle(t_dynamic_helper *d, const unsigned char *in,
	unsigned int *bp)
{
	if (d->code <= 15)
	{
		if (d->i < d->hlit)
			d->bitlen[d->i] = d->code;
		else
			d->bitlen_dst[d->i - d->hlit] = d->code;
		d->i++;
	}
	else if (d->code == 16 || d->code == 17 || d->code == 18)
	{
		if (d->code == 16)
		{
			if ((d->i - 1) < d->hlit)
				d->value = d->bitlen[d->i - 1];
			else
				d->value = d->bitlen_dst[d->i - d->hlit - 1];
		}
		repeat_codes(d, in, bp);
	}
	else
		error_output("FLY YOU FOOLS\n");
}

void			fill_out(t_png *png, t_huffman_helper *s,
	t_huffman *h, const unsigned char *in)
{
	s->distance += ft_read_bits(&h->bit_p, in, s->num_extra_bits_dst);
	s->start = h->pos;
	s->backward = s->start - s->distance;
	if (h->pos + s->length >= png->inflated_size)
		error_output("bail\n");
	s->forward = -1;
	while (++s->forward < s->length)
	{
		png->inflated[h->pos++] = png->inflated[s->backward];
		s->backward++;
		if (s->backward >= s->start)
			s->backward = s->start - s->distance;
	}
}

unsigned int	get_deflate_tree_one(int i)
{
	static unsigned int deflate_code_tree_one[NUM_DEFLATE_CODE_SYMBOLS] = {
	140, 141, 142, 143, 435, 483,
	436, 452, 568, 437, 438, 445, 439, 442, 440, 441, 144, 145, 146, 147, 443,
	444, 148, 149, 150, 151, 446, 449, 447, 448, 152, 153, 154, 155, 450, 451,
	156, 157, 158, 159, 453, 468, 454, 461, 455, 458, 456, 457, 160, 161, 162,
	163, 459, 460, 164, 165, 166, 167, 462, 465, 463, 464, 168, 169, 170, 171,
	466, 467, 172, 173, 174, 175, 469, 476, 470, 473, 471, 472, 176, 177, 178,
	179, 474, 475, 180, 181, 182, 183, 477, 480, 478, 479, 184, 185, 186, 187,
	481, 482, 188, 189, 190, 191, 484, 515, 485, 500, 486, 493, 487, 490, 488,
	489, 192, 193, 194, 195, 491, 492, 196, 197, 198, 199, 494, 497, 495, 496,
	200, 201, 202, 203, 498, 499, 204, 205, 206, 207, 501, 508, 502, 505, 503,
	504, 208, 209, 210, 211, 506, 507, 212, 213, 214, 215, 509, 512, 510, 511,
	216, 217, 218, 219, 513, 514, 220, 221, 222, 223, 516, 531, 517, 524, 518,
	521, 519, 520, 224, 225, 226, 227, 522, 523, 228, 229, 230, 231, 525, 528,
	526, 527, 232, 233, 234, 235, 529, 530, 236, 237, 238, 239, 532, 539, 533,
	536, 534, 535, 240, 241, 242, 243, 537, 538, 244, 245, 246, 247, 540, 543,
	541, 542, 248, 249, 250, 251, 544, 545, 252, 253, 254, 255, 547, 554, 548,
	551, 549, 550, 256, 257, 258, 259, 552, 553, 260, 261, 262, 263, 555, 558,
	556, 557, 264, 265, 266, 267, 559, 560, 268, 269, 270, 271, 562, 565, 563,
	564, 272, 273, 274, 275, 566, 567, 276, 277, 278, 279, 569, 572, 570, 571,
	280, 281, 282, 283, 573, 574, 284, 285, 286, 287, 0, 0 };

	return (deflate_code_tree_one[i]);
}

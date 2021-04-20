/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_trees.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:58:03 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/20 16:18:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void			init_huffman_tree_codetree_fixed(t_huffman_tree *tree,
	unsigned int num_codes, unsigned int maxbitlen)
{
	tree->tree2d = get_fixed_deflate_codetree();
	tree->numcodes = num_codes;
	tree->maxbitlen = maxbitlen;
}

void			init_huffman_tree(t_huffman_tree *tree, unsigned int *buffer,
	unsigned int num_codes, unsigned int maxbitlen)
{
	tree->tree2d = buffer;
	tree->numcodes = num_codes;
	tree->maxbitlen = maxbitlen;
}

unsigned int	*get_fixed_deflate_codetree(void)
{
	static unsigned int	combined_array[NUM_DEFLATE_CODE_SYMBOLS * 2];
	int					i;

	i = 0;
	while (i < (NUM_DEFLATE_CODE_SYMBOLS * 2))
	{
		if (i < NUM_DEFLATE_CODE_SYMBOLS)
			combined_array[i] = get_deflate_tree_zero(i);
		else
			combined_array[i] = get_deflate_tree_one(i);
		i++;
	}
	return ((unsigned int *)combined_array);
}

/*
** i is the current symbol we're reading in the part that contains
** the code lengths of lit/len codes and dist codes
** now we've finally got hlit and hdist, so generate the code trees,
** and the function is done
*/

void			ft_get_tree_inflate_dynamic(t_huffman *h,
	const unsigned char *in, unsigned int inlength)
{
	t_dynamic_helper d;

	if ((h->bit_p) >> 3 >= inlength - 2)
		error_output("bit pointer jumps past memory\n");
	setup_dynamic_helper(&d, in, &h->bit_p);
	ft_huffman_tree_create_lengths(&h->code_length_tree, d.codelengthcode);
	d.i = 0;
	while (d.i < (d.hlit + d.hdist))
	{
		d.code = ft_huffman_decode_symbol(in, &h->bit_p,
			&h->code_length_tree, inlength);
		if ((h->bit_p) >> 3 >= inlength)
			error_output("bit pointer jumps past memory\n");
		dynamic_code_cycle(&d, in, &h->bit_p);
	}
	if (d.bitlen[256] == 0)
		error_output("End code must be larger than 0\n");
	ft_huffman_tree_create_lengths(&h->codetree, d.bitlen);
	ft_huffman_tree_create_lengths(&h->codetree_dst, d.bitlen_dst);
}

void			ft_huffman_tree_create_lengths(t_huffman_tree *tree,
	const unsigned int *bitlen)
{
	t_tree_helper h;

	setup_tree_helper(&h, bitlen, tree);
	h.n = -1;
	while (++h.n < tree->numcodes)
	{
		h.i = -1;
		while (++h.i < bitlen[h.n])
			fill_nodes(&h, tree, bitlen);
	}
	h.n = -1;
	while (++h.n < (tree->numcodes * 2))
	{
		if (tree->tree2d[h.n] == 32767)
			tree->tree2d[h.n] = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:04:14 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/02 09:55:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_STRUCTS_H
# define PARSER_STRUCTS_H

# define MAX_SYMBOLS 288
# define MAX_BIT_LENGTH 15
# define NUM_CODE_LENGTH_CODES 19
# define NUM_DEFLATE_CODE_SYMBOLS 288
# define NUM_COMBINED_ARRAY_SIZE 576
# define NUM_DISTANCE_SYMBOLS 32
# define DEFLATE_CODE_BUFFER_SIZE 576
# define DISTANCE_BUFFER_SIZE 64
# define CODE_LENGTH_BUFFER_SIZE 64

typedef struct s_chunk
{
	unsigned char	length[4];
	char			type[5];
	int				size;
}					t_chunk;

typedef struct s_source
{
	unsigned char	*buf;
	unsigned int	size;
}					t_source;

typedef struct s_scan_helper
{
	unsigned char	*prev;
	unsigned int	line;
	int				byte_width;
	int				line_bytes;
	unsigned int	out_index;
	unsigned int	in_index;
	unsigned char	filter;
}					t_scan_helper;

typedef struct s_png
{
	t_chunk			chunk;
	t_source		source;
	unsigned char	*compressed;
	unsigned char	*pixels;
	unsigned char	*inflated;
	unsigned int	i;
	unsigned int	width;
	unsigned int	height;
	unsigned int	scanline;
	unsigned int	state;
	unsigned int	format;
	unsigned int	compressed_size;
	unsigned int	compressed_index;
	unsigned int	inflated_size;
	unsigned int	final_size;
	unsigned int	depth;
	unsigned int	color_type;
	unsigned int	compression_method;
	unsigned int	filter_method;
	unsigned int	interlace_method;
	unsigned int	channels;
	unsigned int	bpp;
}					t_png;

typedef struct s_crc
{
	unsigned int	crc_table[256];
	int				flag;
}					t_crc;

typedef struct s_texel
{
	unsigned int	*texels;
	int				width;
	int				height;
	int				type;
}				t_texel;

typedef struct s_texture
{
	unsigned char	*source;
	unsigned int	source_size;
	t_texel			tex;
	int				idx;
	int				size;
	int				color_type;
	int				color_depth;
	int				format;
	int				bpp;
	int				pitch;
}					t_texture;

typedef struct s_huffman_tree
{
	unsigned int	*tree2d;
	unsigned int	maxbitlen;
	unsigned int	numcodes;
}					t_huffman_tree;

typedef struct s_tree_helper
{
	unsigned int	tree1d[MAX_SYMBOLS];
	unsigned int	blcount[MAX_BIT_LENGTH];
	unsigned int	nextcode[MAX_BIT_LENGTH + 1];
	unsigned char	bit;
	unsigned int	n;
	unsigned int	i;
	unsigned int	nodefilled;
	unsigned int	treepos;
}					t_tree_helper;

typedef struct s_dynamic_helper
{
	unsigned int	codelengthcode[NUM_CODE_LENGTH_CODES];
	unsigned int	bitlen[NUM_DEFLATE_CODE_SYMBOLS];
	unsigned int	bitlen_dst[NUM_DISTANCE_SYMBOLS];
	unsigned int	n;
	unsigned int	hlit;
	unsigned int	hdist;
	unsigned int	hclen;
	unsigned int	i;
	unsigned int	replength;
	unsigned int	value;
	unsigned int	code;
}					t_dynamic_helper;

typedef struct s_huffman_helper
{
	unsigned int	done;
	unsigned int	code;
	unsigned int	code_dst;
	unsigned int	distance;
	unsigned int	num_extra_bits_dst;
	unsigned int	length;
	unsigned int	start;
	unsigned int	forward;
	unsigned int	backward;
	unsigned int	numextrabits;
}					t_huffman_helper;

typedef struct s_huffman
{
	t_huffman_tree	codetree;
	t_huffman_tree	codetree_dst;
	t_huffman_tree	code_length_tree;
	unsigned int	codetree_buffer[DEFLATE_CODE_BUFFER_SIZE];
	unsigned int	codetree_dst_buffer[DISTANCE_BUFFER_SIZE];
	unsigned int	code_length_tree_buffer[CODE_LENGTH_BUFFER_SIZE];
	unsigned int	bit_p;
	unsigned int	pos;
	unsigned int	type;
}					t_huffman;

#endif

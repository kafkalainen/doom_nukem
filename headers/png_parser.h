/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:01:38 by rzukale           #+#    #+#             */
/*   Updated: 2021/07/21 16:14:43 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PNG_PARSER_H
# define PNG_PARSER_H

# define MAX_SIZE 16777216
# define COLOR_LUM 0
# define COLOR_RGB 2
# define COLOR_LUMA 4
# define COLOR_RGBA 6
# define RGB_8 1
# define RGB_16 2
# define RGBA_8 3
# define RGBA_16 4
# define LUM_1 5
# define LUM_2 6
# define LUM_4 7
# define LUM_8 8
# define LUM_ALPHA_1 9
# define LUM_ALPHA_2 10
# define LUM_ALPHA_4 11
# define LUM_ALPHA_8 12
# define FIRST_LENGTH_CODE_INDEX 257
# define LAST_LENGTH_CODE_INDEX 285
# define DEFLATE_CODE_BITLEN 15
# define DISTANCE_BITLEN 15
# define CODE_LENGTH_BITLEN 7

/*
** Filtering functions
*/

void			paeth(unsigned char *out, unsigned char *sl,
					t_scan_helper s);
int				predict(int a, int b, int c);
void			avg(unsigned char *out, unsigned char *sl,
					t_scan_helper s);
void			up(unsigned char *out, unsigned char *sl,
					t_scan_helper s);
void			sub(unsigned char *out, unsigned char *sl,
					t_scan_helper s);

/*
** CRC functions
*/

void			verify_crc(unsigned char *crc_buf, unsigned char *buf,
					int size, t_crc *crc);
unsigned int	calculate_crc(unsigned char *buf, int size, t_crc *crc);
unsigned int	update_crc(unsigned int crcbuf, unsigned char *buf,
					int size, t_crc *crc);
void			init_crc_table(t_crc *crc);

/*
** Header functions
*/

void			check_header(t_png *png);
int				color_depth_restrictions(int color, int depth);
void			get_header_elements(t_png *png);
int				get_format(int color_type, int color_depth);
void			validate_signature(unsigned char *buf);

/*
** Parsing functions
*/

void			verify_chunks(t_png *png);
void			setup_parser(t_png *png, unsigned int size);
void			decode_png(t_png *png);
void			parse_data(t_png *png);
void			parse_png(t_png *png);
t_png			png_parser(char *path);

/*
** t_texture struct functions
*/

t_texture		*create_texture(t_png *png, int idx);
void			free_texture(t_texture *tex);
t_texture		*assign_empty_texture(void);
void			convert_to_unsigned_int(t_texture *tex, t_png *png);
unsigned int	add_pixel(unsigned char *data, int bpp, int pos);
void			add_texture_values(t_png *png, t_texture *tex, int idx);

/*
** Unfiltering functions
*/

void			process_scanline(unsigned char *out,
					unsigned char *sl, t_scan_helper s);
void			unfilter_scanlines(t_png *png, unsigned char *out,
					unsigned char *in);
void			convert_to_pixels(t_png *png);

/*
**	Inflate algorithm functions
*/

unsigned int	ft_read_bits(unsigned int *bitp,
					const unsigned char *bitstream, unsigned int nbits);
unsigned char	ft_read_bit(unsigned int *bitp,
					const unsigned char *bitstream);
void			ft_inflate(t_png *png);
void			ft_inflate_data(t_png *png);
void			go_go_huffman(t_png *png, const unsigned char *in,
					t_huffman *h);
void			ft_inflate_uncompressed(t_png *png, const unsigned char *in,
					unsigned int *bp, unsigned int *pos);
void			ft_inflate_huffman(t_png *png, const unsigned char *in,
					t_huffman *h);
unsigned int	get_deflate_tree_one(int i);
void			fill_out(t_png *png, t_huffman_helper *s,
					t_huffman *h, const unsigned char *in);
void			dynamic_code_cycle(t_dynamic_helper *d, const unsigned char *in,
					unsigned int *bp);
unsigned int	ft_huffman_decode_symbol(const unsigned char *in,
					unsigned int *bp, t_huffman_tree *codetree,
					unsigned int inlength);
void			fill_nodes(t_tree_helper *h, t_huffman_tree *tree,
					const unsigned int *bitlen);
void			check_code(t_huffman_helper *s, t_png *png, t_huffman *h);
void			repeat_codes(t_dynamic_helper *d, const unsigned char *in,
					unsigned int *bp);
void			get_nbits_replength(unsigned int *nbits, unsigned int code,
					unsigned int *replength);
void			ft_huffman_tree_create_lengths(t_huffman_tree *tree,
					const unsigned int *bitlen);
void			ft_get_tree_inflate_dynamic(t_huffman *h,
					const unsigned char *in, unsigned int inlength);
unsigned int	*get_fixed_deflate_codetree(void);
void			init_huffman_tree(t_huffman_tree *tree,
					unsigned int *buffer,
					unsigned int num_codes, unsigned int maxbitlen);
void			init_huffman_tree_codetree_fixed(t_huffman_tree *tree,
					unsigned int num_codes, unsigned int maxbitlen);
unsigned int	get_deflate_tree_zero(int i);
void			get_dst_base_extra(unsigned int *distance,
					unsigned int *num_extra_bits_dst, unsigned int code_dst);
void			get_length_base_extra(unsigned int *length,
					unsigned int *num_extra_bits_dst, unsigned int code);
void			setup_tree_helper(t_tree_helper *h, const unsigned int *bitlen,
					t_huffman_tree *tree);
void			setup_dynamic_helper(t_dynamic_helper *d,
					const unsigned char *in, unsigned int *bp);
/*
** Utility functions
*/

void			check_idat(t_png *png);
void			check_end(t_png *png);
int				check_depth(int depth);
int				get_big_endian(unsigned char *buf);
void			get_current_chunk(t_chunk *chunk,
					unsigned char *buf, int i);
int				get_color_rgba(int depth);
int				get_color_rgb(int depth);
int				get_color_lum(int depth);
int				get_color_luma(int color_depth);
void			error_output(char *msg);
void			free_png(t_png png);
void			assemble_idat_chunks(t_png *png);

#endif

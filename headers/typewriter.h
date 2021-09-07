/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typewriter.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 09:46:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/06 18:42:31 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEWRITER_H
# define TYPEWRITER_H

# define TEXT_SIZE 2
# define MAIN_MENU_TEXT 5

typedef struct s_pxl_c
{
	int			c[36];
}				t_pxl_c;

typedef struct s_plx_modifier
{
	Uint32		colour;
	int			size;
	size_t		len;
}				t_plx_modifier;

t_pxl_c			pxl_alphabet(int l, int b, int c);
t_pxl_c			pxl_numbers(int l, int b, int c);
void			ft_str_pxl(t_buffer *buffer, t_xy coord, char *str,
					t_plx_modifier mod);
void			ft_c_pxl(t_buffer *buffer, t_xy coord, char c, t_plx_modifier mod);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typewriter.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 09:46:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/12 12:45:29 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEWRITER_H
# define TYPEWRITER_H
# define TEXT_SIZE 2

typedef struct	s_pxl_c
{
	int			c[36];
}				t_pxl_c;

t_pxl_c			pxl_alphabet(int l, int b, int c);
t_pxl_c			pxl_numbers(int l, int b, int c);
void			str_pxl(Uint32 *buffer, t_xy coord, char *str);
#endif

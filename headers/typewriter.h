/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typewriter.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 09:46:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/14 11:38:47 by jnivala          ###   ########.fr       */
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

typedef	struct s_plx_modifier
{
	int		colour;
	int		size;
}				t_plx_modifier;


t_pxl_c			pxl_alphabet(int l, int b, int c);
t_pxl_c			pxl_numbers(int l, int b, int c);
void			str_pxl(Uint32 *buffer, t_xy coord, char *str, t_plx_modifier mod);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:48:09 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/21 09:40:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CALCULATIONS_H
# define CALCULATIONS_H

typedef	struct		s_intersection
{
	float	x1;
	float	x2;
	float 	y1;
	float	y2;
	float	den;
	float	neg;
	float	pos;
}					t_intersection;

void		calc_intersection(t_polygon *pgon, t_xy *pos, t_xy *dir, 
					t_intersection *sect);
t_xy		line_intersection(t_intersection *sect);

#endif
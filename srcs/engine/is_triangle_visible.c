/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_triangle_visible.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:28:03 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/17 12:44:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	Because our engine is running in reverse, we have visibility check if that
**	if dot product is less than zero.
*/
t_bool	is_triangle_visible(t_triangle *viewed_tri, t_xyz pos)
{
	if (vec3_dot_product(viewed_tri->normal,
		vec3_dec(viewed_tri->p[0], pos)) < 0)
		return (true);
	else
		return (false);
}

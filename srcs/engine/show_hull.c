/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_hull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:04:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/21 09:10:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	show_hull(t_triangle *viewed_tri)
{
	initialize_lumels(&viewed_tri->lu[0], &viewed_tri->lu[1],
		&viewed_tri->lu[2], 0.275f);
	viewed_tri->type = -wall7;
}

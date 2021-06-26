/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lighting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:06:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/25 12:55:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	To get the average unit normal vector at a vertex,
**	we take the average of the normals of the neighboring faces.
**	Since the resulting normal should be a unit normal,
**	we can do the averaging by summing all the neighboring normals,
**	and then dividing by the magnitude of this sum.
**	Create a normal[3] set to triangle to store average of
**	neighboring normals.
**	Apply Blinn-Phong's reflection model.
*/

void	set_lighting(t_lighting *light, t_triangle *tri, t_xyz normal)
{
	(void)light;
	(void)normal;
	// if (light)
	// {
	// 	if (light->state)
	// 	{
	// 		tri->illumination = ft_fmax(
	// 			vec3_dot_product(light->light_dir, normal), 0.1f);
	// 		tri->illumination = ft_fmin(tri->illumination * 4, 1.0f);
	// 	}
	// 	else
	// 		tri->illumination = ft_fmax(
	// 			vec3_dot_product(light->light_dir, normal), 0.1f);
	// }
	// else
	tri->illumination = 1.0f;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lighting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:06:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 14:16:02 by jnivala          ###   ########.fr       */
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
**	Should there always be at least 6 neighbouring triangles?
**	Y-axis needs to be interpolated properly at draw_tex_triangle.
**	Triangle vertex normals are calculated incorrectly.
*/

static float	saturate(float value)
{
	if (value < 0.0f)
		value = ft_fabsf(value);
	else if (value > 1.0f)
		value = 1.0f;
	else
		value = value;
	return (value);
}

/*
**	Decided to use Lambertial lighting model
**	opposed to Blinn-Phong lighting model.
*/
static float	calculate_light_intensity(t_lighting *light, t_triangle *tri,
				Uint32 idx)
{
	t_xyz	light_dir;
	float	magnitude;
	float	dot_product;
	float	intensity;

	light_dir = vec3_unit_vector(vec3_dec(light->light_src, tri->p[idx]));
	magnitude = vec3_eucl_dist(light_dir);
	magnitude = magnitude * magnitude;
	dot_product = vec3_dot_product(light_dir, tri->normal);
	intensity = saturate(dot_product);
	intensity = intensity * light->diffuse_power * 0.1f / magnitude;
	if (intensity < 0.1f)
		intensity = 0.1f;
	return (intensity);
}

static float	calculate_enemy_light_intensity(t_lighting *light,
				t_triangle *tri, Uint32 idx)
{
	t_xyz	light_dir;
	float	magnitude;
	float	dot_product;
	float	intensity;

	light_dir = vec3_unit_vector(vec3_dec(light->light_src, tri->p[idx]));
	magnitude = vec3_eucl_dist(light_dir);
	magnitude = magnitude * magnitude;
	dot_product = vec3_dot_product(light_dir, (t_xyz){0.0f, 1.0f, 0.0f, 1.0f});
	intensity = saturate(dot_product);
	intensity = intensity * light->diffuse_power * 0.1f / magnitude;
	if (intensity < 0.1f)
		intensity = 0.1f;
	return (intensity);
}

void	set_lighting(t_lighting *light, t_triangle *tri)
{
	if (light)
	{
		if (light->state == TRUE && light->diffuse_power > 0.0f)
		{
			if (tri->idx == -enemy0 || tri->idx == -enemy1)
			{
				tri->lu[0] = calculate_enemy_light_intensity(light, tri, 0);
				tri->lu[1] = calculate_enemy_light_intensity(light, tri, 1);
				tri->lu[2] = calculate_enemy_light_intensity(light, tri, 2);
			}
			else if (tri->idx == -bullet)
				initialize_lumels(&tri->lu[0], &tri->lu[1], &tri->lu[2], 1.0f);
			else
			{
				tri->lu[0] = calculate_light_intensity(light, tri, 0);
				tri->lu[1] = calculate_light_intensity(light, tri, 1);
				tri->lu[2] = calculate_light_intensity(light, tri, 2);
			}
		}
		else
			initialize_lumels(&tri->lu[0], &tri->lu[1], &tri->lu[2], 0.1f);
	}
	else
		initialize_lumels(&tri->lu[0], &tri->lu[1], &tri->lu[2], 1.0f);
}

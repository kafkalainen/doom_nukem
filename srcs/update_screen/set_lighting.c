/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lighting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:06:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/29 11:43:44 by jnivala          ###   ########.fr       */
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
		value = 0.0f;
	else if (value > 1.0f)
		value = 1.0f;
	else
		value = value;
	return (value);
}

void	set_lighting(t_lighting *light, t_triangle *tri, t_xyz plr_pos)
{
	Uint32	i;
	t_xyz	light_dir;
	float	magnitude;
	float	dot_product;
	float	intensity;

	i = 0;
	(void)plr_pos;
	if (light)
	{
		if (light->state == TRUE && light->diffuse_power > 0)
		{
			while (i < 3)
			{
				light_dir = vec3_dec(light->light_src, tri->p[i]);
				magnitude = vec3_eucl_dist(light_dir);
				light_dir = vec3_unit_vector(light_dir);
				magnitude = magnitude * magnitude;
				dot_product = vec3_dot_product(tri->vertex_normal[i], light_dir);
				intensity = saturate(dot_product);
				tri->lu[i] = intensity * light->diffuse_power / magnitude;
				// //Calculate the half vector between the light vector and the view vector.
				// //This is typically slower than calculating the actual reflection vector
				// // due to the normalize function's reciprocal square root
				// float3 H = normalize(lightDir + viewDir);

				// //Intensity of the specular light
				// float NdotH = dot(normal, H);
				// intensity = pow(saturate(NdotH), specularHardness);

				// //Sum up the specular light factoring
				// OUT.Specular = intensity * light.specularColor * light.specularPower / distance;
				if (tri->lu[i] < 0.1f)
					tri->lu[i] = 0.1f;
				i++;
			}
		}
		else
		{
			tri->lu[0] = 0.1f;
			tri->lu[1] = 0.1f;
			tri->lu[2] = 0.1f;
		}
	}
	else
	{
		tri->lu[0] = 1.0f;
		tri->lu[1] = 1.0f;
		tri->lu[2] = 1.0f;
	}
}

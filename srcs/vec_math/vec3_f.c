/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 19:43:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/28 16:00:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xyz	vec3_calc_vector_average(t_raster_queue	*queue)
{
	int		i;
	t_xyz	average;
	float	denom;

	i = queue->front;
	average = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	if (queue->size == 0)
		return ((t_xyz){0.0f, 0.0f, 0.0f, 0.0f});
	while (i < queue->rear)
	{
		average = vec3_add(average, queue->array[i].normal);
		i++;
	}
	denom = 1.0f / vec3_eucl_dist(average);
	average = vec3_unit_vector(vec3_mul(average, denom));
	return (average);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 19:43:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/07 14:30:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xyz	vec3_calc_vector_average(t_raster_queue	*queue)
{
	int		i;
	t_xyz	average;

	i = queue->front;
	average = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	if (queue->size == 0)
		return ((t_xyz){0.0f, 0.0f, 0.0f, 0.0f});
	while (i < queue->rear)
	{
		average = vec3_add(average, queue->array[i].normal);
		i++;
	}
	average = vec3_unit_vector(average);
	return (average);
}

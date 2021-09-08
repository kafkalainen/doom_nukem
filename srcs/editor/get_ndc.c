/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ndc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 09:01:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/08 10:23:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	get_ndc(t_buffer *buffer, t_screen_xy coord)
{
	int	cur_width;

	cur_width = buffer->width - TOOLBAR_WIDTH;
	return (vec2((
		((coord.x - TOOLBAR_WIDTH) - 0.5f * cur_width) / (float)cur_width) * 2.0f,
		(((buffer->height - coord.y) - 0.5f * buffer->height)
		/ (float)buffer->height) * 2.0f));
}

// t_screen_xy	ndc_to_screen(t_buffer *buffer, t_xy coord)
// {

// 	return (vec2(((
// 		coord.x - 0.5f * buffer->width) / (float)buffer->width) * 2.0f,
// 		(((buffer->height - coord.y) - 0.5f * buffer->height)
// 		/ (float)buffer->height) * 2.0f));
// }

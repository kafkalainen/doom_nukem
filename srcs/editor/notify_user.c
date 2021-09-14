/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:11:48 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/14 13:47:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	show_user_help(char *str, t_buffer *buffer, int layer, Uint32 colour)
{
	t_plx_modifier	mod;
	t_xy			offset;

	if (!str)
		return ;
	offset = (t_xy){0.0f, 0.0f, 1.0f};
	mod.colour = colour;
	mod.len = ft_strlen((const char *)str);
	mod.size = TEXT_SIZE;
	if (mod.len > 0)
	{
		offset.x = 0.5f * (buffer->width - (mod.len * mod.size * 5));
		if (mod.len % 2)
			offset.x -= (mod.size * 5 * 0.5f);
		offset.y = 100.0f + layer * 9 * mod.size;
		ft_str_pxl(buffer, offset, str, mod);
	}
}

void	notify_user(char **str, t_buffer *buffer, Uint32 delta_time,
		int *notify_time)
{
	t_plx_modifier	mod;
	t_xy			offset;

	if (!*str)
		return ;
	if (*notify_time > 0)
	{
		*notify_time -= delta_time;
		offset = (t_xy){0.0f, 0.0f, 1.0f};
		mod.colour = get_color(orange);
		mod.len = ft_strlen((const char *)*str);
		mod.size = TEXT_SIZE;
		if (mod.len > 1)
		{
			offset.x = 0.5f * (buffer->width - (mod.len * mod.size * 5));
			if (mod.len % 2)
				offset.x -= (mod.size * 5 * 0.5f);
			offset.y = 100.0f;
		}
		ft_str_pxl(buffer, offset, *str, mod);
	}
	else
		ft_strdel(str);
}

void	add_notification(t_editor *editor, char *message, int amount)
{
	if (editor->notification != NULL)
		return ;
	editor->notification = ft_strdup(message);
	editor->notify_time = amount;
}

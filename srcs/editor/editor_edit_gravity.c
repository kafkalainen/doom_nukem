/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit_gravity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:01:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/01 14:45:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	editor_edit_gravity(t_editor *editor)
{
	if (!editor->temp_sector)
		return ;
	if (editor->temp_sector->gravity == 2)
		editor->temp_sector->gravity = 4;
	else if (editor->temp_sector->gravity == 4)
		editor->temp_sector->gravity = 10;
	else if (editor->temp_sector->gravity == 10)
		editor->temp_sector->gravity = 23;
	else if (editor->temp_sector->gravity == 23)
		editor->temp_sector->gravity = 2;
	editor->action.set_gravity = false;
}

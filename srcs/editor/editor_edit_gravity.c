/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit_gravity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:01:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/01 12:49:29 by rzukale          ###   ########.fr       */
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
		editor->temp_sector->gravity = 6;
	else if (editor->temp_sector->gravity == 6)
		editor->temp_sector->gravity = 10;
	else if (editor->temp_sector->gravity == 10)
		editor->temp_sector->gravity = 2;
	editor->action.set_gravity = false;
}

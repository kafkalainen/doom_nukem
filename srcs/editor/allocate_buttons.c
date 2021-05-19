/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:42 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/18 11:53:12 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

void	create_button(t_button *list, t_xy ltop, t_xy wh, char *text)
{
	list->ltop = ltop;
	list->wh = wh;
	list->text = malloc(sizeof(char) * (ft_strlen((const char *)text) + 1));
	if (!list->text)
		error_output("Memory allocation failed\n");
	list->text = ft_strcpy(list->text, (const char *)text);
}

t_button	**create_button_list(t_button **blist)
{
	int i;

	i = 0;
	while (i < NBR_BUTTONS)
		blist[i++] = (t_button*)malloc(sizeof(t_button));
	i = 0;
	create_button(blist[i++], vec2(32, 52), vec2(96, 76), "Print sector data");
	create_button(blist[i++], vec2(32, 80), vec2(96, 104), "Toggle grid");
	create_button(blist[i++], vec2(32, 134), vec2(24, 158), "++");
	create_button(blist[i++], vec2(76, 134), vec2(24, 158), "--");
	create_button(blist[i++], vec2(16, 180), vec2(96, 204), "New sector");
	create_button(blist[i++], vec2(120, 180), vec2(24, 204), "-");
	create_button(blist[i++], vec2(164, 180), vec2(24, 204), "+");
	create_button(blist[i++], vec2(16, 240), vec2(168, 264), "Delete selected sector");
	create_button(blist[i++], vec2(16, 280), vec2(168, 304), "Snap sector to grid");
	create_button(blist[i++], vec2(16, 320), vec2(178, 344), "Show sectors' bboxes");
	create_button(blist[i++], vec2(16, 360), vec2(110, 384), "Sector z:");
	create_button(blist[i++], vec2(16, 390), vec2(110, 314), "Sector height:");
	create_button(blist[i++], vec2(16, 420), vec2(110, 444), "Sector floor tex:");
	create_button(blist[i], vec2(16, 450), vec2(110, 474), "Sector ceiling tex:");
	return(blist);
}

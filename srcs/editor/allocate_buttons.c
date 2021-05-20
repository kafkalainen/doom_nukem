/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:42 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/20 13:56:35 by rzukale          ###   ########.fr       */
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
	create_button(blist[i++], vec2(32, 52), vec2(220, 76), "Print sector data");
	create_button(blist[i++], vec2(32, 80), vec2(160, 104), "Toggle grid");
	create_button(blist[i++], vec2(64, 134), vec2(100, 158), "++");
	create_button(blist[i++], vec2(105, 134), vec2(141, 158), "--");
	create_button(blist[i++], vec2(32, 180), vec2(150, 204), "New sector");
	create_button(blist[i++], vec2(155, 180), vec2(180, 204), "-");
	create_button(blist[i++], vec2(185, 180), vec2(210, 204), "+");
	create_button(blist[i++], vec2(32, 240), vec2(270, 264), "Delete selected sector");
	create_button(blist[i++], vec2(32, 280), vec2(240, 304), "Snap sector to grid");
	create_button(blist[i++], vec2(32, 320), vec2(250, 344), "Show sectors' bboxes");
	create_button(blist[i++], vec2(32, 360), vec2(140, 384), "Sector z:");
	create_button(blist[i++], vec2(32, 390), vec2(150, 314), "Sector height:");
	create_button(blist[i++], vec2(32, 420), vec2(220, 444), "Sector floor tex:");
	create_button(blist[i], vec2(32, 450), vec2(240, 474), "Sector ceiling tex:");
	return(blist);
}

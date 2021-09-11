/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:54:30 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/11 12:08:29 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	create_button(t_button *list, t_box box, t_button_info info)
{
	list->info.inputfield = info.inputfield;
	list->info.draw_depth = info.draw_depth;
	list->ltop = box.start;
	list->wh = box.end;
	list->info.text = (char *)malloc(sizeof(char)
			* (ft_strlen((const char *)info.text) + 1));
	if (!list->info.text)
		error_output("Memory allocation failed\n");
	list->info.text = ft_strcpy(list->info.text, (const char *)info.text);
}

static int	buttons_create_general_layer(t_button **blist, int i)
{
	create_button(blist[i++], (t_box){vec2(32, 52), vec2(195, 75)},
		(t_button_info){"Save map", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 80), vec2(195, 105)},
		(t_button_info){"Load map", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 110), vec2(195, 135)},
		(t_button_info){"Toggle grid = G", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 140), vec2(185, 165)},
		(t_button_info){"New Sector = F", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 170), vec2(215, 195)},
		(t_button_info){"Assign end sector", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 200), vec2(195, 225)},
		(t_button_info){"Link map", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 230), vec2(195, 255)},
		(t_button_info){"Unlink map", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 260), vec2(235, 285)},
		(t_button_info){"Assign player start", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 290), vec2(195, 315)},
		(t_button_info){"Create elevator", 0, depth_zero});
	return (i);
}

static int	buttons_create_sector_layer(t_button **blist, int i)
{
	create_button(blist[i++], (t_box){vec2(32, 52), vec2(185, 75)},
		(t_button_info){"Sector idx:", 0, sector});
	create_button(blist[i++], (t_box){vec2(32, 80), vec2(220, 105)},
		(t_button_info){"Sector floor tex:", 0, sector});
	create_button(blist[i++], (t_box){vec2(32, 215), vec2(240, 235)},
		(t_button_info){"Sector ceiling tex:", 0, sector});
	create_button(blist[i++], (t_box){vec2(32, 345), vec2(235, 370)},
		(t_button_info){"Set Light intensity", 1, sector});
	create_button(blist[i++], (t_box){vec2(32, 375), vec2(195, 400)},
		(t_button_info){"Is elevator", 1, sector});
	create_button(blist[i++], (t_box){vec2(32, 405), vec2(210, 430)},
		(t_button_info){"Add light source", 1, sector});
	create_button(blist[i++], (t_box){vec2(32, 435), vec2(205, 460)},
		(t_button_info){"Write plot", 1, sector});
	return (i);
}

static int	buttons_create_wall_layer(t_button **blist, int i)
{
	create_button(blist[i++], (t_box){vec2(32, 52), vec2(275, 75)},
		(t_button_info){"wall index:", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 80), vec2(275, 105)},
		(t_button_info){"Wall texture:", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 225), vec2(275, 250)},
		(t_button_info){"Convert to portal", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 255), vec2(245, 280)},
		(t_button_info){"wall ceiling height:", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 285), vec2(245, 310)},
		(t_button_info){"wall floor height:", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 315), vec2(275, 335)},
		(t_button_info){"Add light button", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 340), vec2(275, 365)},
		(t_button_info){"Add powerstation", 0, wall});
	return (i);
}

t_button	**create_button_list(t_button **blist)
{
	int	i;

	i = 0;
	while (i < NBR_BUTTONS)
		blist[i++] = (t_button *)malloc(sizeof(t_button));
	i = 0;
	i = buttons_create_general_layer(blist, i);
	i = buttons_create_sector_layer(blist, i);
	i = buttons_create_wall_layer(blist, i);
	create_button(blist[i++], (t_box){vec2(32, 52), vec2(95, 75)},
		(t_button_info){"Index", 0, entity});
	create_button(blist[i++], (t_box){vec2(32, 80), vec2(90, 105)},
		(t_button_info){"Type", 0, entity});
	create_button(blist[i++], (t_box){vec2(32, 225), vec2(140, 250)},
		(t_button_info){"Is linked", 0, entity});
	create_button(blist[i++], (t_box){vec2(32, 255), vec2(160, 280)},
		(t_button_info){"Is revealed", 0, entity});
	create_button(blist[i++], (t_box){vec2(32, 285), vec2(140, 315)},
		(t_button_info){"Is static", 0, entity});
	create_button(blist[i], (t_box){vec2(32, 320), vec2(95, 345)},
		(t_button_info){"State", 0, entity});
	return (blist);
}

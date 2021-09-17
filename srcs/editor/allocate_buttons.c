/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:54:30 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/17 12:05:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	create_button(t_button *list, t_box box, t_button_info info)
{
	list->mod.len = ft_strlen((const char *)info.text);
	list->mod.size = TEXT_SIZE;
	list->mod.colour = get_color(white);
	list->info.inputfield = info.inputfield;
	list->info.draw_depth = info.draw_depth;
	list->box = box;
	list->info.text = ft_strdup((const char *)info.text);
	if (!list->info.text)
		error_output("Memory allocation failed.");
	list->text_loc.x = box.start.x + 0.5f * ((box.end.x - box.start.x) -
		(list->mod.len * list->mod.size * 5));
	if (list->mod.len % 2)
		list->text_loc.x -= (list->mod.size * 5 * 0.5f);
	list->text_loc.y = box.start.y + list->mod.size * 7 * 0.5f;
}

static int	buttons_create_general_layer(t_button **blist, int i)
{
	create_button(blist[i++], (t_box){vec2(32, 52), vec2(235, 75)},
		(t_button_info){"Save map", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 80), vec2(235, 105)},
		(t_button_info){"Load map", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 110), vec2(235, 135)},
		(t_button_info){"Toggle grid = G", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 140), vec2(235, 165)},
		(t_button_info){"Assign end sector", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 170), vec2(235, 195)},
		(t_button_info){"Link map", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 200), vec2(235, 225)},
		(t_button_info){"Unlink map", 0, depth_zero});
	create_button(blist[i++], (t_box){vec2(32, 230), vec2(235, 255)},
		(t_button_info){"Assign player start", 0, depth_zero});
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
		(t_button_info){"Set light intensity", 1, sector});
	create_button(blist[i++], (t_box){vec2(32, 375), vec2(195, 400)},
		(t_button_info){"Convert sector to a lift", 1, sector});
	create_button(blist[i++], (t_box){vec2(32, 405), vec2(210, 430)},
		(t_button_info){"Add light source", 1, sector});
	create_button(blist[i++], (t_box){vec2(32, 435), vec2(205, 460)},
		(t_button_info){"Write plot", 1, sector});
	create_button(blist[i++], (t_box){vec2(32, 465), vec2(275, 490)},
		(t_button_info){"Create portal between sectors", 0, sector});
	create_button(blist[i++], (t_box){vec2(32, 495), vec2(275, 520)},
		(t_button_info){"Set all ceiling heights", 0, sector});
	create_button(blist[i++], (t_box){vec2(32, 525), vec2(275, 550)},
		(t_button_info){"Set all floor heights", 0, sector});
	return (i);
}

static int	buttons_create_wall_layer(t_button **blist, int i)
{
	create_button(blist[i++], (t_box){vec2(32, 52), vec2(275, 75)},
		(t_button_info){"wall index:", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 80), vec2(275, 105)},
		(t_button_info){"Wall texture:", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 255), vec2(245, 280)},
		(t_button_info){"wall ceiling height:", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 285), vec2(245, 310)},
		(t_button_info){"wall floor height:", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 315), vec2(275, 335)},
		(t_button_info){"Add light button", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 340), vec2(275, 365)},
		(t_button_info){"Add powerstation", 0, wall});
	create_button(blist[i++], (t_box){vec2(32, 370), vec2(275, 395)},
		(t_button_info){"Add elevator button", 0, wall});
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

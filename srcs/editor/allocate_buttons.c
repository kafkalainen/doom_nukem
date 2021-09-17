/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:54:30 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/17 14:24:05 by jnivala          ###   ########.fr       */
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
	list->text_loc.x = box.start.x + list->mod.size * 5 * 0.5f
		+ 0.5f * ((box.end.x - box.start.x) - (list->mod.len * list->mod.size * 5));
	if (list->mod.len % 2)
		list->text_loc.x -= (list->mod.size * 5 * 0.5f);
	list->text_loc.y = box.start.y + list->mod.size * 7 * 0.5f;
}

static void	buttons_create_general_layer(t_button **blist)
{
	create_button(blist[0], (t_box){vec2(48, 52), vec2(251, 75)},
		(t_button_info){"Save map", 0, depth_zero});
	create_button(blist[1], (t_box){vec2(48, 80), vec2(251, 105)},
		(t_button_info){"Load map", 0, depth_zero});
	create_button(blist[2], (t_box){vec2(48, 110), vec2(251, 135)},
		(t_button_info){"Toggle grid = G", 0, depth_zero});
	create_button(blist[3], (t_box){vec2(48, 140), vec2(251, 165)},
		(t_button_info){"Assign end sector", 0, depth_zero});
	create_button(blist[4], (t_box){vec2(48, 170), vec2(251, 195)},
		(t_button_info){"Link map", 0, depth_zero});
	create_button(blist[5], (t_box){vec2(48, 200), vec2(251, 225)},
		(t_button_info){"Unlink map", 0, depth_zero});
	create_button(blist[6], (t_box){vec2(48, 230), vec2(251, 255)},
		(t_button_info){"Assign player start", 0, depth_zero});
}

static void	buttons_create_sector_layer(t_button **blist)
{
	create_button(blist[7], (t_box){vec2(10, 52), vec2(290, 75)},
		(t_button_info){"Sector idx:", 0, sector});
	create_button(blist[8], (t_box){vec2(10, 80), vec2(290, 105)},
		(t_button_info){"Sector floor tex:", 0, sector});
	create_button(blist[9], (t_box){vec2(10, 215), vec2(290, 235)},
		(t_button_info){"Sector ceiling tex:", 0, sector});
	create_button(blist[10], (t_box){vec2(10, 375), vec2(190, 400)},
		(t_button_info){"Convert sector to a lift", 1, sector});
	create_button(blist[11], (t_box){vec2(10, 405), vec2(290, 430)},
		(t_button_info){"Add light source", 1, sector});
	create_button(blist[12], (t_box){vec2(10, 345), vec2(290, 370)},
		(t_button_info){"Set light intensity", 1, sector});
	create_button(blist[13], (t_box){vec2(10, 435), vec2(290, 460)},
		(t_button_info){"Write plot", 1, sector});
	create_button(blist[14], (t_box){vec2(10, 465), vec2(290, 490)},
		(t_button_info){"Create portal to sector", 0, sector});
	create_button(blist[15], (t_box){vec2(10, 525), vec2(290, 550)},
		(t_button_info){"Set all ceiling heights", 0, sector});
	create_button(blist[16], (t_box){vec2(10, 555), vec2(290, 580)},
		(t_button_info){"Set all floor heights", 0, sector});
}

static void	buttons_create_wall_layer(t_button **blist)
{
	create_button(blist[17], (t_box){vec2(32, 52), vec2(275, 75)},
		(t_button_info){"wall index:", 0, wall});
	create_button(blist[18], (t_box){vec2(32, 80), vec2(275, 105)},
		(t_button_info){"Wall texture:", 0, wall});
	create_button(blist[19], (t_box){vec2(32, 255), vec2(245, 280)},
		(t_button_info){"wall ceiling height:", 0, wall});
	create_button(blist[20], (t_box){vec2(32, 285), vec2(245, 310)},
		(t_button_info){"wall floor height:", 0, wall});
	create_button(blist[21], (t_box){vec2(32, 315), vec2(275, 335)},
		(t_button_info){"Add light button", 0, wall});
	create_button(blist[22], (t_box){vec2(32, 340), vec2(275, 365)},
		(t_button_info){"Add powerstation", 0, wall});
	create_button(blist[23], (t_box){vec2(32, 370), vec2(275, 395)},
		(t_button_info){"Add elevator button", 0, wall});
	create_button(blist[24], (t_box){vec2(10, 400), vec2(290, 425)},
		(t_button_info){"Change to door", 0, sector});
}

t_button	**create_button_list(t_button **blist)
{
	int	i;

	i = 0;
	while (i < NBR_BUTTONS)
		blist[i++] = (t_button *)malloc(sizeof(t_button));
	buttons_create_general_layer(blist);
	buttons_create_sector_layer(blist);
	buttons_create_wall_layer(blist);
	create_button(blist[25], (t_box){vec2(32, 52), vec2(95, 75)},
		(t_button_info){"Index", 0, entity});
	create_button(blist[26], (t_box){vec2(32, 80), vec2(90, 105)},
		(t_button_info){"Type", 0, entity});
	create_button(blist[27], (t_box){vec2(32, 225), vec2(140, 250)},
		(t_button_info){"Is linked", 0, entity});
	create_button(blist[28], (t_box){vec2(32, 255), vec2(160, 280)},
		(t_button_info){"Is revealed", 0, entity});
	create_button(blist[29], (t_box){vec2(32, 285), vec2(140, 315)},
		(t_button_info){"Is static", 0, entity});
	create_button(blist[30], (t_box){vec2(32, 320), vec2(95, 345)},
		(t_button_info){"State", 0, entity});
	return (blist);
}

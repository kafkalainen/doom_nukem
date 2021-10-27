/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:54:30 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/11 10:17:56 by rzukale          ###   ########.fr       */
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
	list->is_active = true;
	list->box = box;
	list->info.text = ft_strdup((const char *)info.text);
	if (!list->info.text)
		error_output("Memory allocation failed.");
	list->text_loc.x = center_text_x_axis(box.start.x, box.end.x,
			list->mod.size, list->mod.len);
	list->text_loc.y = (box.start.y - 1) + list->mod.size * 7 * 0.5f;
}

static void	buttons_create_general_layer(t_button **blist)
{
	create_button(blist[0], (t_box){vec2(48, 50), vec2(251, 75)},
		(t_button_info){"Save map", 0, depth_zero});
	create_button(blist[1], (t_box){vec2(48, 80), vec2(251, 105)},
		(t_button_info){"Load map", 0, depth_zero});
	create_button(blist[2], (t_box){vec2(48, 110), vec2(251, 135)},
		(t_button_info){"Toggle grid", 0, depth_zero});
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
	create_button(blist[7], (t_box){vec2(10, 50), vec2(290, 75)},
		(t_button_info){"Sector idx:", 0, sector});
	create_button(blist[8], (t_box){vec2(10, 80), vec2(290, 105)},
		(t_button_info){"Sector floor tex:", 0, sector});
	create_button(blist[9], (t_box){vec2(10, 215), vec2(290, 240)},
		(t_button_info){"Sector ceiling tex:", 0, sector});
	create_button(blist[10], (t_box){vec2(10, 350), vec2(290, 375)},
		(t_button_info){"Convert sector to a lift", 1, sector});
	create_button(blist[11], (t_box){vec2(10, 380), vec2(290, 405)},
		(t_button_info){"Add light source", 1, sector});
	create_button(blist[12], (t_box){vec2(10, 410), vec2(290, 435)},
		(t_button_info){"Set light intensity", 1, sector});
	create_button(blist[13], (t_box){vec2(10, 440), vec2(290, 465)},
		(t_button_info){"Write sector plot", 1, sector});
	create_button(blist[14], (t_box){vec2(10, 470), vec2(290, 495)},
		(t_button_info){"Create portal to sector", 0, sector});
	create_button(blist[15], (t_box){vec2(10, 500), vec2(290, 525)},
		(t_button_info){"Set all ceiling heights", 0, sector});
	create_button(blist[16], (t_box){vec2(10, 530), vec2(290, 555)},
		(t_button_info){"Set all ground heights", 0, sector});
	create_button(blist[17], (t_box){vec2(10, 560), vec2(290, 585)},
		(t_button_info){"Set gravity", 0, sector});
}

static void	buttons_create_wall_layer(t_button **blist)
{
	create_button(blist[18], (t_box){vec2(10, 50), vec2(290, 75)},
		(t_button_info){"Wall index:", 0, wall});
	create_button(blist[19], (t_box){vec2(10, 80), vec2(290, 105)},
		(t_button_info){"Wall texture:", 0, wall});
	create_button(blist[20], (t_box){vec2(10, 245), vec2(290, 270)},
		(t_button_info){"wall ceiling height:", 0, wall});
	create_button(blist[21], (t_box){vec2(10, 275), vec2(290, 300)},
		(t_button_info){"Wall floor height:", 0, wall});
	create_button(blist[22], (t_box){vec2(10, 305), vec2(290, 330)},
		(t_button_info){"Add light button", 0, wall});
	create_button(blist[23], (t_box){vec2(10, 335), vec2(290, 360)},
		(t_button_info){"Add powerstation", 0, wall});
	create_button(blist[24], (t_box){vec2(10, 365), vec2(290, 390)},
		(t_button_info){"Add lift button", 0, wall});
	create_button(blist[25], (t_box){vec2(10, 395), vec2(290, 420)},
		(t_button_info){"Add Poster", 0, wall});
	create_button(blist[26], (t_box){vec2(10, 425), vec2(290, 450)},
		(t_button_info){"Cycle through portals", 0, wall});
}

t_button	**create_button_list(t_button **blist)
{
	int	i;

	i = 0;
	while (i < NBR_BUTTONS)
	{
		blist[i] = (t_button *)malloc(sizeof(t_button));
		if (!blist[i])
			error_output("Error when output allocating buttons.");
		i++;
	}
	buttons_create_general_layer(blist);
	buttons_create_sector_layer(blist);
	buttons_create_wall_layer(blist);
	create_button(blist[27], (t_box){vec2(10, 50), vec2(290, 75)},
		(t_button_info){"Index", 0, entity});
	create_button(blist[28], (t_box){vec2(10, 80), vec2(290, 105)},
		(t_button_info){"Type", 0, entity});
	create_button(blist[29], (t_box){vec2(10, 225), vec2(290, 250)},
		(t_button_info){"Light controls", 0, entity});
	create_button(blist[30], (t_box){vec2(10, 255), vec2(290, 280)},
		(t_button_info){"Alternative texture", 0, entity});
	create_button(blist[31], (t_box){vec2(10, 285), vec2(290, 310)},
		(t_button_info){"State", 0, entity});
	return (blist);
}

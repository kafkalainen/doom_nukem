/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:10:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 09:42:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	init_asset_textures(t_home *home)
{
	load_texture("textures/power_station_ready.png",
		home->textures, power_station_ready);
	load_texture("textures/power_station_depleted.png",
		home->textures, power_station_depleted);
	load_texture("textures/button_on.png", home->textures, button_on);
	load_texture("textures/button_off.png", home->textures, button_off);
	load_texture("textures/lamp_on.png", home->textures, lamp_on);
	load_texture("textures/lamp_off.png", home->textures, lamp_off);
	load_texture("textures/bullet_decal.png", home->textures, bullet_decal);
}

static void	init_wall_and_floor_textures(t_home *home)
{
	load_texture("textures/armory.png", home->textures, wall0);
	load_texture("textures/green_wall.png", home->textures, wall1);
	load_texture("textures/loading_bay.png", home->textures, wall2);
	load_texture("textures/rusty_wall.png", home->textures, wall3);
	load_texture("textures/white.png", home->textures, wall4);
	load_texture("textures/rusty_window.png", home->textures, small_window);
	load_texture("textures/bridge_window.png", home->textures, large_window);
	load_texture("textures/hull2.png", home->textures, wall7);
	load_texture("textures/yellow.png", home->textures, wall8);
	load_texture("textures/white.png", home->textures, wall9);
	load_texture("textures/rusty_floor.png", home->textures, surf0);
	load_texture("textures/floor_tile.png", home->textures, surf1);
	load_texture("textures/grate.png", home->textures, surf2);
	load_texture("textures/grate2.png", home->textures, surf3);
	load_texture("textures/metal_sheet.png", home->textures, surf4);
	load_texture("textures/steel_rust.png", home->textures, surf5);
	load_texture("textures/clean_floor.png", home->textures, surf6);
	load_texture("textures/scraps.png", home->textures, surf7);
	load_texture("textures/hull.png", home->textures, surf8);
	load_texture("textures/plate.png", home->textures, surf9);
}

static void	init_pickupables(t_home *home)
{
	load_texture("textures/ammo_pack.png", home->textures,
		ammo_pack_sprite);
	load_texture("textures/cleaning_key.png", home->textures,
		cleaning_keycard_sprite);
	load_texture("textures/engineering_key.png", home->textures,
		engineering_keycard_sprite);
	load_texture("textures/military_key.png", home->textures,
		military_keycard_sprite);
}

/*
**	Current number of textures is 43
*/
void	init_textures(t_home *home)
{
	home->textures = (t_texture **)malloc(sizeof(t_texture *) * NUM_TEX);
	if (!home->textures)
		error_output("Failed to allocate memory to editor textures.\n");
	home->textures[zero] = assign_empty_texture();
	load_texture("textures/dsky.png", home->textures, space);
	init_wall_and_floor_textures(home);
	load_texture("textures/door.png", home->textures, door);
	load_texture("textures/hud_doom.png", home->textures, hud);
	load_texture("textures/pistol.png", home->textures, weapon0);
	load_texture("textures/plate.png", home->textures, weapon1);
	load_texture("textures/skull_skulker.png", home->textures, enemy0);
	load_texture("textures/thing.png", home->textures, enemy1);
	load_texture("textures/skull_skulker.png", home->textures, enemy2);
	load_texture("textures/crewmember.png", home->textures, enemy3);
	load_texture("textures/plasma_ball.png", home->textures, bullet);
	load_texture("textures/muzzle.png", home->textures, muzzleflash);
	load_texture("textures/hull_window_large.png", home->textures,
		hull_large_window);
	load_texture("textures/hull_window_small.png", home->textures,
		hull_small_window);
	init_pickupables(home);
	init_asset_textures(home);
	home->textures[NUM_TEX - 1] = assign_empty_texture();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:36:51 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/05 21:55:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

enum e_plot_states
{
	no_plot,
	sector_plot,
	beginning1,
	beginning2,
	beginning3,
	beginning4,
	beginning5,
	talk1,
	talk2,
	talk3,
	talk4,
	talk5,
	talk6,
	talk7,
	talk8,
	ending1,
	ending2,
	ending3,
	ending4,
	ending5,
	ending6,
	ending7,
	ending8,
	ending9,
	cutscene1,
	cutscene2,
	enemy_sighted,
	enemy_noise_before,
	enemy_noise_after,
	power_on,
	first_blood,
	health_low,
};

typedef struct s_input
{
	int				right;
	int				left;
	int				up;
	int				down;
	int				rot_right;
	int				rot_left;
	int				crouch;
	int				jump;
	int				wireframe;
	int				minimap;
	t_bool			music;
	int				info;
	int				mouse;
	int				jetpack;
	int				use;
	int				shoot;
	int				debug_up;
	int				debug_down;
	int				debug_left;
	int				debug_right;
}					t_input;

/*
** HUD struct
** Reasoning:
** "viewmodel" triangles are for the player gun/hand etc. plane
** made separate from the HUD layer in order to easily manipulate the layer
** eg. gun walking "animation", png animation, lightning and such
**
** ammo stuff and especially power_points is there mostly as a reminder.
** do we have them somewhere? Should they go to player struct?
**
** damage_effect_instensity will be a fade timer for a "hurt" effect.
*/
typedef struct s_hud
{
	t_triangle		*viewmodel;
	t_triangle		*hud;

	int				idx[2];
	unsigned int	viewmodel_frame;
	float			damage_effect_intensity;
	float			hud_hp_x;
	float			hud_hp_y;
	float			hud_ammo_x;
	float			hud_ammo_y;
	float			hud_fuel_x;
	float			hud_fuel_y;
	float			vm_x;
	float			vm_y;
	float			vm_mx;
	float			vm_my;
	float			vm_rx;
	float			vm_ry;
}					t_hud;

/*
**	Type: Projectile or scan
*/
typedef struct s_weapon
{
	unsigned int	ammo;
	unsigned int	type;
	float			fire_rate;
}					t_weapon;

typedef struct s_inventory
{
	t_bool			in_use;
	int				sprite_idx;
}				t_inventory;

typedef struct s_player
{
	t_audio			audio;
	t_hud			hud;
	t_input			input;
	t_weapon		wep[2];
	t_triangle		tri[4];
	t_inventory		inventory[4];
	t_xyz			pos;
	t_xyz			test_pos;
	t_xyz			look_dir;
	t_xyz			move_dir;
	t_xyz			target;
	t_xyz			up;
	t_xyz			speed;
	t_xy			dir;
	float			yaw;
	float			steps;
	float			pitch;
	float			roll;
	float			height;
	float			width;
	float			acceleration;
	float			power_points;
	float			fuel_points;
	float			dead;
	int				cur_sector;
	int				msg_sector;
	int				plot_state;
	int				active_inv;
	int				enemy_sighted;
	Uint32			time;
	Uint32			message_time;
	Uint32			display_object;
	Uint32			reload;
	unsigned int	active_wep;
}					t_player;

enum e_movement
{
	open_space = -9999
};

/*
** Player functions
*/

t_entity		*activate_object(t_home *home, t_player *plr);
t_wall			*check_if_crossing(t_sector *sector, t_xyz pos, t_xyz dir);
t_bool			check_if_open_portal(t_wall *wall);
t_xyz			check_y(t_sector *sector, t_player *plr, t_xyz pos);
t_bool			check_distance_to_ceiling(t_sector *sector, t_xyz *new_loc);
float			check_distance_to_ground(t_sector *sector, float height,
					t_xyz pos);
t_bool			check_for_matching_key(t_wall *wall, t_player *plr,
					int keycard);
Uint32			update_doors(t_sector **sectors, Uint32 nb_of_sectors,
					Uint32 current_time, Uint32 delta_time);
void			create_target_vector(t_player *plr);
void			crouch(t_player *plr);
void			draw_plot_state(t_home *home, Uint32 *buffer, t_player *plr);
void			end_level(t_home *home, t_player *plr);
t_bool			evolve_story(t_player *plr, t_sector *sector,
					t_sector *msg_sector);
void			free_story(char ***array, Uint32 nb_of_strings);
float			get_wall_hit_point(t_home *home, t_ray *ray,
					t_bullet_hole *hole, int bullet_sector);
t_bullet_hole	get_bullet_hit_point(t_home *home, t_ray *ray,
					int bullet_sector);
float			get_ceiling_hit_point(t_sector *sector, t_ray *ray,
					t_bullet_hole *hole);
float			get_entity_hit_point(t_home *home, t_ray *ray,
					t_bullet_hole *hole, int bullet_sector);
float			get_ground_hit_point(t_sector *sector, t_ray *ray,
					t_bullet_hole *hole);
float			get_player_hit_point(t_ray *ray, t_bullet_hole *hole,
					int bullet_sector);
void			gravity(t_sector *sector, t_player *plr, Uint32 delta_time);
void			initialize_player_target_triangles(t_player *plr);
void			init_cutscene(char **array);
void			initialize_player(t_player *plr);
char			**init_story(void);
t_bool			jetpack(t_player *plr, t_home *home, Uint32 t);
void			jump(t_player *plr, t_sector *cur_sector);
t_bool			player_move(t_player *plr, t_home *home, Uint32 t);
int				plr_inside(t_sector *sector, t_player *plr);
int				player_use(t_player *plr, t_home *home);
t_bool			open_door(t_sector **sectors, t_player *plr, int active_item);
t_bool			player_look(t_home *home, t_player *plr);
void			player_place_feet_to_ground(t_home *home, t_player *plr);
int				player_use_inventory_item(t_player *plr);
void			update_player(t_player *plr, t_home *home, Uint32 delta_time);
void			shooting_handle(t_home *home, t_ray *ray);
Uint32			strafe_along_the_wall(t_wall *wall, t_player *plr,
					t_home *home, Uint32 t);
Uint32			test_triangle(t_triangle *tri, t_bullet_hole *hole_2, float *d,
					t_ray *ray);
void			player_take_damage(t_player *plr, Uint32 damage, Uint32 time);
void			reload_weapon(t_player *plr, Uint32 t);

#endif

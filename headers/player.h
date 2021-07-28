/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:36:51 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/21 14:02:28 by jnivala          ###   ########.fr       */
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

typedef struct		s_hud
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

typedef struct		s_weapon
{
	unsigned int	ammo;
	unsigned int	type; //projectile or shitscan
	float			fire_rate;
}					t_weapon;

typedef struct		s_player
{
	t_hud			hud;
	t_input			input;
	t_xyz			pos;
	t_xyz			look_dir;
	t_xyz			move_dir;
	t_xyz			target;
	t_xyz			up;
	t_xy			dir;
	t_xyz			speed;
	float			yaw;
	float			pitch;
	float			height;
	float			acceleration;
	int				cur_sector;
	int				msg_sector;
	int				plot_state;
	int				enemy_sighted;
	int				active_inv;
	float			power_points;
	float			fuel_points;
	t_weapon		wep[2];
	unsigned int	active_wep;
	unsigned int	inventory[4];
	float			steps;
	Uint32			time;
	Uint32			message_time;
	t_audio			audio;
}					t_player;

enum e_movement
{
	open_space = -9999
};


/*
** Player functions
*/

t_wall	*check_if_crossing(t_sector *sector, t_xyz pos);
t_xyz	check_y(t_sector *sector, t_player *plr, t_xyz pos);
int		check_y_diff(t_player *plr, t_xyz *test_pos, t_sector *to);
Uint32	check_distance_to_ceiling(t_sector *sector, t_xyz *new_loc);
float	check_distance_to_ground(t_sector *sector, t_player *plr, t_xyz pos);
Uint32	close_doors(t_sector **sectors, Uint32 nb_of_sectors,
		Uint32 current_time, Uint32 delta_time);
void	create_target_vector(t_player *plr);
void	crouch(t_player *plr);
void	end_level(t_home *home, t_player *plr);
void	gravity(t_sector *sector, t_player *plr, Uint32 delta_time);
void	init_player(t_player *plr);
int		jetpack(t_player *plr, t_home *home, Uint32 t);
void	jump(t_player *plr, t_sector *cur_sector);
int		open_door(t_sector **sectors, t_xyz look_loc,
		Uint32 current_time, Uint32 cur_sector);
int		player_move(t_player *plr, t_home *home, Uint32 delta_time);
int		plr_inside(t_sector *sector, t_player *plr);
int		player_use(t_player *plr, t_home *home, Uint32 delta_time);
void	update_player(t_player *plr, t_home *home, Uint32 delta_time);
char	**init_story(void);
void	free_story(char ***array, Uint32 nb_of_strings);
Uint32	evolve_story(t_player *plr, t_sector *sector, t_sector *msg_sector);
void	draw_plot_state(t_home *home, Uint32 *buffer, t_player *plr);
void	init_cutscene(char **array);
void	shooting_handle(t_home *home, t_player *plr);

#endif

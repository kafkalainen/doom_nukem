/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:36:51 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/01 16:23:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

enum e_plot_states
{
	beginning,
	enemy_sighted,
	contemplation,
	warning,
	plot_twist,
	ending,
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
}					t_hud;


typedef struct		s_player
{
	t_input			input;
	t_xyz			pos;
	t_xyz			look_dir;
	t_xyz			move_dir;
	t_xyz			target;
	t_xyz			up;
	t_xy			dir;
	float			yaw;
	float			pitch;
	float			height;
	float			acceleration;
	int				cur_sector;
	int				plot_state;
	int				enemy_sighted;
	float			power_points;
	unsigned int	active_wep;
	unsigned int	active_inv;
	unsigned int	live_ammo[2];
	unsigned int	reserve_ammo[2];
	unsigned int	inventory[4];
	t_hud			*hud;
	Uint32			time;
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

#endif

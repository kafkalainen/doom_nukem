/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:08:38 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 16:41:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTOR_H
# define SECTOR_H

/*
**	top and bottom triangle have all texture and positional data for the
**	wall.
**	is_door = is portal a door.
**	is_closed = is portal currently closed.
**	is_locked = is portal currently locked.
**	0 = unlocked
**	1 = temporarily locked
**	2 = cleaning keycard
**	3 = engineering keycard
**	4 = military keycard
**	open_until tells how long the door is open.
**	height tells the height of the wall for locking.
**	next gives the next memory address for a wall.
*/
typedef struct s_wall
{
	t_triangle			top;
	t_triangle			bottom;
	Uint32				is_door;
	Uint32				is_closed;
	Uint32				is_locked;
	Uint32				open_until;
	float				height;
	struct s_wall		*next;
}						t_wall;

/*
**	light_src tells the position of the light source.
**	diffuse_power is the power of the light
**	is_linked can have following values.
**	0	not linked
**	1	automatic
**	2+	linked button entity
**	light state is boolean that if it is on or off
*/
typedef struct s_lighting
{
	t_xyz				light_src;
	float				diffuse_power;
	Uint32				is_linked;
	Uint32				state;
}				t_lighting;

typedef struct s_surface
{
	t_triangle			tri;
	struct s_surface	*next;
}						t_surface;

typedef struct s_skybox
{
	int					idx;
	t_triangle			*face;
}						t_skybox;

typedef struct s_point_data
{
	float		x;
	float		y;
	float		ground;
	float		ceiling;
	int			idx;
	int			light_switch;
	int			on_off;
	int			power_station;
}				t_point_data;

typedef struct s_entity_data
{
	float		x;
	float		y;
	float		ground;
	int			entity_type;
	int			is_static;
}				t_entity_data;

typedef struct s_sector
{
	t_wall			*walls;
	t_surface		*ground;
	t_surface		*ceiling;
	t_lighting		lights;
	t_plgn			bounding_box;
	float			velocity;
	Uint32			is_lift;
	Uint32			elevator_dir;
	Uint32			moving_until;
	Uint32			nb_of_msgs;
	unsigned int	nb_of_walls;
	unsigned int	nb_of_ceil;
	unsigned int	nb_of_ground;
	unsigned int	cur_msg;
	int				idx_sector;
	int				tex_floor;
	int				tex_ceil;
	char			**story;
}					t_sector;

enum e_sector_info
{
	old_sector = -6666
};

t_wall			*new_point(t_point_data *left, t_point_data *right);
void			add_point(t_wall **point, t_wall *new);

#endif

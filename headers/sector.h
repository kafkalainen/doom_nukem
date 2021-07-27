/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:08:38 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/27 16:44:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTOR_H
# define SECTOR_H

typedef struct s_power_station
{
	Uint32	is_power_station;
	Uint32	is_depleted;
}				t_power_station;

typedef struct s_light_switch
{
	Uint32	is_switch;
	Uint32	on_off;
}				t_light_switch;

typedef struct s_wall
{
	t_triangle			top;
	t_triangle			bottom;
	t_power_station		station;
	t_light_switch		light_switch;
	Uint32				is_door;
	Uint32				is_closed;
	Uint32				open_until;
	float				height;
	struct s_wall		*next;
}						t_wall;

typedef	struct s_lighting
{
	t_xyz				light_src;
	float				diffuse_power;
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

typedef struct s_sector
{
	t_wall			*walls;
	unsigned int	nb_of_walls;
	unsigned int	nb_of_ceil;
	unsigned int	nb_of_ground;
	int				idx_sector;
	int				tex_floor;
	int				tex_ceil;
	char			**story;
	unsigned int	nb_of_msgs;
	unsigned int	cur_msg;
	t_lighting		lights;
	t_surface		*ground;
	t_surface		*ceiling;
	t_plgn			bounding_box;
}					t_sector;

enum e_sector_info
{
	old_sector = -6666
};

t_wall			*new_point(t_point_data *left, t_point_data *right);
void			add_point(t_wall **point, t_wall *new);

#endif

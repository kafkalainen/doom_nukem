/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:08:38 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/06 12:20:55 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTOR_H
# define SECTOR_H

typedef struct s_point
{
	t_xy				x0;
	int					idx;
	float				wall_facing;
	t_xy				normal;
	t_height			height;
	struct s_point		*next;
}						t_point;

typedef struct s_point_data
{
	float		x;
	float		y;
	int			ground;
	int			ceiling;
	int			idx;
}				t_point_data;

typedef struct s_sector
{
	t_point			*points;
	t_enemy			*enemies;
	unsigned int	nb_of_walls;
	int				idx_sector;
	int				tex_floor;
	int				tex_ceil;
	int				ground;
	int				ceiling;
	t_xyz			floor_top_left;
	t_xyz			floor_top_right;
	t_xyz			floor_bottom_left;
	t_xyz			floor_bottom_right;
}					t_sector;

enum e_sector_info
{
	old_sector = -6666
};

t_point			*new_point(t_point_data *data);
void			add_point(t_point **point, t_point *new);

#endif

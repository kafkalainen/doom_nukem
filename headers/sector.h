/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:12:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/01 12:11:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTOR_H
# define SECTOR_H

typedef struct			s_polygon
{
	t_xy				x0;
	t_xy				normal;
	int					idx;
	float				wall_rad;
	struct s_polygon	*next;
}						t_point;

typedef struct		s_sector
{
	t_point		*points;
	t_enemy			*enemies;
	int				nb_of_walls;
	int				idx_sector;
	int				tex_floor;
	int				tex_ceil;
	float			ground;
	float			ceiling;
}					t_sector;

t_point	*new_polygon(t_xy x0, int idx);

#endif

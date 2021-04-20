/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:08:38 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/23 10:53:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTOR_H
# define SECTOR_H

typedef struct			s_point
{
	t_xy				x0;
	int					idx;
	char				c;
	struct s_point		*next;
}						t_point;

typedef struct		s_sector
{
	t_point			*points;
	t_enemy			*enemies;
	int				nb_of_walls;
	int				idx_sector;
	int				tex_floor;
	int				tex_ceil;
	float			ground;
	float			ceiling;
	t_xyz			floor_top_left;
	t_xyz			floor_top_right;
	t_xyz			floor_bottom_left;
	t_xyz			floor_bottom_right;
}					t_sector;

t_point			*new_point(t_xy x0, int idx);
t_point			*add_point(t_point **point, t_point *new);
t_point			*loop_list(t_point *head, t_point *current);

#endif

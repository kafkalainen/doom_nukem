/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dn_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:12:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/20 13:14:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DN_MAP_H
# define DN_MAP_H
# include "doom_nukem.h"


typedef struct			t_p_data
{
	t_xy				x0;
	t_xy				normal;
	int					connection;
}

typedef struct			s_polygon
{
	t_xy				x0;
	t_xy				normal;
	int					idx;
	int					connection;
	struct s_polygon	*next;
}						t_polygon;

typedef struct		s_sector
{
	t_polygon		*polygons;
	t_enemy			*enemies;
	int				nb_of_walls;
	int				idx_sector;
	int				tex_floor;
	int				tex_ceil;
	double			ground;
	double			ceiling;
}					t_sector;

int		update_sector(t_home *home);

#endif

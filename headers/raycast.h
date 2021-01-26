/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/26 16:59:57 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

t_ray_fov			get_fov_points(t_polygon *plgn, t_home *home, t_player *plr, int i);
void				calc_intersection(t_polygon *pgon, t_polygon *first, t_ray *ray,
						t_intersection *sect);
t_xy				line_intersection(t_intersection *sect);
#endif

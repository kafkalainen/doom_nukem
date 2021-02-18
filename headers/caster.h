/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:51:14 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/09 09:52:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CASTER_H
# define CASTER_H

/*
** Raycaster
*/

void			draw_tex_col(t_tex_col *tex, float distance, SDL_Surface *surf);
void			draw_wall(int col, t_wall wall, t_xy ray, t_home *home, t_player *plr);
void			draw_fov_floor(t_home *home, t_player *plr);

t_xy			init_ray(t_xy pos, t_xy plane, t_xy left, float angle);
t_wall			cast_ray(t_xy pos, t_xy ray);
void			draw_fov(t_home *home, t_player *plr);
void			draw_2d(t_home *home, t_frame *frame, t_player *plr);

#endif

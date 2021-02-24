/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:49:25 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/23 15:16:38 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_FUNCTIONS_H
# define DRAWING_FUNCTIONS_H

/*
** Drawing functions
*/

void			clear_surface(SDL_Surface *surface);
int				ft_put_pixel(float x, float y, int color, SDL_Renderer *ren);
int				ft_draw_line(t_xy start, t_xy end, int color, SDL_Surface *surf);
// int				ft_draw_line(t_xy start, t_xy end, t_texture *tex, SDL_Surface *surf);
void			draw_rect_center(t_xy xy, t_xy wh, t_frame *frame);
void			draw_rect(t_xy xy, t_xy wh, t_frame *frame, int color);
void			put_pixel(SDL_Surface *surf, int x, int y, int color);
t_step			*steplen(t_step *ground, int current_y, t_ray_floor hor,
	t_player *plr);
Uint32			get_pixel(SDL_Surface *surface, int x, int y);

#endif

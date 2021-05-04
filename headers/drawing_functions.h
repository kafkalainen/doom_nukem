/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:49:25 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/04 10:03:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_FUNCTIONS_H
# define DRAWING_FUNCTIONS_H

/*
** Drawing functions
*/

Uint32		colour_scale(Uint32 hex, float scale);
int			draw_line(t_xy start, t_xy end, Uint32 color, Uint32 *buffer);
void		draw_rect_center(t_xy xy, t_xy wh, t_frame *frame);
void		draw_rect(t_xy xy, t_xy wh, t_frame *frame, Uint32 color);
void		draw_tex_pixel(t_texture *tex, t_xyz texel,
				t_xy pixel, t_frame *frame);
void		draw_wireframe(t_frame *frame, Uint32 colour);
void		put_pixel(Uint32 *buffer, int x, int y, Uint32 color);
Uint32		get_pixel(SDL_Surface *surface, int x, int y);
t_xy		center_to_screen(t_xy loc);
void		render_buffer(Uint32 *buffer, SDL_Surface *screen_surface);
void		*optimized_memcpy(void *pixels, void *src, size_t size);

#endif

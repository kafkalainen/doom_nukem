/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:49:25 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/20 12:19:49 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_FUNCTIONS_H
# define DRAWING_FUNCTIONS_H

/*
** Drawing functions
*/

Uint32		colour_scale(Uint32 hex, float scale);
int			draw_line(t_xy start, t_xy end, Uint32 color, t_buffer *buffer);
void		draw_rect_center(t_xy xy, t_xy wh, t_frame *frame);
void		draw_rect(t_xy xy, t_xy wh, t_buffer *buffer, int color);
void		draw_square(t_buffer *buffer, t_xy offset, int c, int s);
void		draw_wireframe(t_frame *frame, Uint32 colour);
void		put_pixel(t_buffer *buffer, t_pxl_coords xy, Uint32 color);
Uint32		get_texel(int x, int y, t_texture *tex);
t_xy		center_to_screen(t_xy loc);
void		render_buffer(Uint32 *buffer, SDL_Surface *screen_surface);
void		*optimized_memcpy(void *pixels, void *src, size_t size);

#endif

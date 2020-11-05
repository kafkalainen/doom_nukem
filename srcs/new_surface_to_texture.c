/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_surface_to_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:52:12 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/05 19:12:47 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h"

SDL_Texture *new_surface_to_texture(char *filename, SDL_Renderer *ren)
{
    SDL_Surface *bmp;
    SDL_Texture *tex;
    bmp = SDL_LoadBMP(filename);
    if (bmp == NULL)
        ft_die("Failed to load BMP image.");
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL)
        ft_die("Failed to create texture from surface.");
    return (tex);
}

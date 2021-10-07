/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:45:17 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/07 13:18:03 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define NBR_BUTTONS 31
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

# define FOV 1.57079616f
# define ZOOM_OUT_MAX 0.015625f
# define ZOOM_IN_MAX 0.25f

/*
**  Number of textures has been counted as follows:
**  - Zero index
**  - 20 available wall and floor textures.
**  - HUD
**  - 2 weapons
**  - 4 enemies
**  - Ammo projectile
**  - Health station full / depleted
**  - Switch on / off
**  - Door
**  - Lamp on / off
*/
# define NUM_TEX 46
# define MAX_FILE_NAME_LENGTH 50
# define MAX_INT 2147483647
# define PI_BY_TWO 1.570796326f
# define PI 3.1415926535f
# define TWO_PI 6.283185307f
# define SQR2 0.7071067812f
# define Z_NEAR 0.1f
# define Z_FAR 1000.0f
# define OPEN_DOOR_DISTANCE 3.25f
# define MAIN_SETTINGS 6
# define GAME_CONTINUE 5
# define EDITOR 4
# define GAME_LOOP 3
# define MAP_MENU 2
# define MAIN_MENU 1
# define QUIT -1
# define MAX_THREADS 6
# define DOOR_INDEX 3000
# define CLEANING_INDEX 6000
# define ENGINEERING_INDEX 9000
# define MILITARY_INDEX 12000
# define SECRET_INDEX 15000
# define SMALL_WINDOW_INDEX 18000
# define LARGE_WINDOW_INDEX 21000
# define SUBDIV 16.0f
# define DENOMSUBDIV 0.0625f
# define SMALL_ENEMY 80
# define LARGE_ENEMY 64
# define EASY 0.75f
# define NORMAL 1.0f
# define HARD 1.25f

/*
** Compass directions
*/

# define N 6.28318530718f
# define NW 0.7853981634f
# define W 1.5707963268f
# define SW 2.3561944902f
# define S 3.14159265359f
# define SE 3.926990817f
# define E 4.71238898039f
# define NE 5.49778714378f

#endif

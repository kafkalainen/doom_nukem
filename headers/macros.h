/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:45:17 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/21 21:20:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define BUFF_SIZE 16
# define NBR_BUTTONS 14
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

# define TEX_SIZE 128
# define FOV 1.57079616f
# define MAP_MAX_LINES 128
# define MINIMAP_SIZE 10
# define HUD_HP_X 100.0f
# define HUD_HP_Y 540.0f
# define HUD_AMMO_X 630.0f
# define HUD_AMMO_Y 570.0f
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
# define NUM_TEX 36
# define MAX_INT 2147483647
# define PLR_DIR 0.785398163f
# define INV_PI_BY_TWO 0.1591549367f
# define PI 3.1415926535f
# define PI_BY_TWO 1.570796326f
# define TWO_PI 6.283185307f
# define RAD_TO_DEG 57.29577951f
# define DEG_TO_RAD 0.0174532925f
# define SQR2 0.7071067812f
# define Z_NEAR 0.1f
# define Z_FAR 1000.0f
# define TRUE 1
# define FALSE 0
# define AND &&
# define OR ||
# define GAME_CONTINUE 5
# define EDITOR 4
# define GAME_LOOP 3
# define MAP_MENU 2
# define MAIN_MENU 1
# define QUIT -1
# define MAX_THREADS 6
# define SKYBOX_TEX -1
# define DOOR_INDEX 3000
# define SUBDIV 16.0f
# define DENOMSUBDIV 0.0625f
# define STORY_STRINGS 30

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

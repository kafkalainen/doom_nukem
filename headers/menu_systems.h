/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_systems.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:27:23 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/11 14:29:47 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_SYSTEMS_H
# define MENU_SYSTEMS_H

void	process_inputs_load_menu(int *game_state, SDL_Event *e, int *option, int nbr_of_maps);
void	process_inputs_main_menu(int *game_state, SDL_Event *e);
void	launch_load_menu_loop(t_home *home, Uint32 **buffer, SDL_Event *e);
void	launch_game_loop(t_home *home, t_player *plr, t_frame *frame, SDL_Event *e);

#endif

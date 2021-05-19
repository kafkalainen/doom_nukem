/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <eparvia@student.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:29:25 by eparviai          #+#    #+#             */
/*   Updated: 2021/05/11 12:29:25 by eparviai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

typedef struct		s_mouse_data
{
	float			x;
	float			y;
	int				selected;
	int				i_mbleft;
	int				i_mbright;
	float			x_rel;
	float			y_rel;
}					t_mouse_data;

/* typedef struct		s_sector_list 
{ 
	t_sector 		*sector;
	t_bbox			bbox;
	t_sector_list	*next;
}					t_sector_list ; */

typedef struct		s_button
{
	t_xy		ltop;
	t_xy		wh;
	char		*text;
}					t_button;

typedef struct		s_editor
{
	//t_sector_list	*sector_list;
	t_button		**button_list;
	t_mouse_data	*mouse_data;
	Uint32			*buffer;
	t_window		win;
	int				grid_size;
	int				toggle_grid;
}					t_editor;

// SDL DRAWING STUFF

void		editor_events(SDL_Event *e, t_home *home, t_editor *editor);
void		draw_ui(t_editor *editor);
void		check_event(t_mouse_data *mouse_data, t_button **list);
void		launch_editor(t_home *home, SDL_Event *e);
t_button	**create_button_list(t_button **blist);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:29:25 by eparviai          #+#    #+#             */
/*   Updated: 2021/05/19 15:53:34 by rzukale          ###   ########.fr       */
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

typedef	struct		s_int_xy
{
	int				width;
	int				height;
}					t_int_xy;

typedef	struct		s_box
{
	t_xy			start;
	t_xy			end;
}					t_box;


typedef struct		s_editor
{
	//t_sector_list	*sector_list;
	t_button		**button_list;
	t_mouse_data	mouse_data;
	Uint32			*buffer;
	t_window		win;
	t_int_xy		win_dim;
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

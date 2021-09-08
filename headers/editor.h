/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:29:25 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/08 17:32:09 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# define TOOLBAR_WIDTH 300

typedef struct		s_mouse_data
{
	int				x;
	int				y;
	float			x_rel;
	float			y_rel;
	int				selected;
	int				i_mbleft;
	int				i_mbright;
}					t_mouse_data;

typedef struct s_editor_walls
{
	t_screen_xy				x0;
	t_screen_xy				norm;
	t_height				height;
	t_box					bbox;
	int						idx;
	int						type;
	struct s_editor_walls	*next;
}				t_editor_walls;

/*
**	intensity between 0-100, can be rescaled on gamesetup between 0-1
*/

typedef	struct s_editor_light
{
	t_screen_xy	pos;
	int			intensity;
	int			is_linked;
	int			state;
}				t_editor_light;

typedef	struct s_button_info
{
	char		*text;
	int			inputfield;
	int			draw_depth;
}					t_button_info;

typedef struct s_button
{
	t_button_info	info;
	t_xy			ltop;
	t_xy			wh;

}					t_button;

typedef	struct s_plr_pos
{
	int				x;
	int				z;
	int				sector;
}					t_plr_pos;


typedef struct s_action
{
	t_screen_xy		offset;
	t_xy			offsetf;
	t_xy			mouse_pos;
	t_xy			world_pos;
	int				grid;
	int				new_sector;
	int				selected_sector;
	int				selected_point;
	int				selected_entity;
	int				selected_wall;
	int				scalar;
	float			scalarf;
	int				create_sector;
	int				create_entity;
	int				link_entity;
	int				unlink_entity;
	int				prev_entity;
	int				edit_sector;
	int				input_active;
	int				keysym;
	int				prev_keysym;
	int				move;
	int				open_file;
	int				link_maps;
	int				unlink_maps;
	int				save_file;
	int				draw_depth;
	int				delete;
	int				edit_entity;
	int				change_entity_type;
	int				toggle_entity_is_linked;
	int				toggle_is_revealed;
	int				toggle_is_static;
	int				toggle_state;
	int				create_elevator;
	int				create_elev_button;
	int				create_light_button;
	int				create_powerstation;
	int				assign_end_sector;
	int				assign_player_start;
	int				map_name_set;
	int				player_start_assigned;
	int				option;
	int				nbr_of_maps;
	int				start;
	int				end;
	int				edit_wall;
	int				change_wall_texture;
	int				change_floor_texture;
	int				change_ceiling_texture;
	int				convert_to_portal;
	int				edit_ceiling_height;
	int				edit_floor_height;
	int				set_light_intensity;
	int				create_light_source;
	int				add_wall_point;
}					t_action;

typedef	struct s_editor_xyz
{
	int				x;
	int				y;
	int				z;
}					t_editor_xyz;

typedef	struct s_entity_list
{
	t_box					bbox;
	t_editor_xyz			pos;
	t_editor_xyz			dir;
	int						entity_idx;
	int						entity_type;
	int						sector_idx;
	int						is_static;
	int						is_active;
	int						is_revealed;
	int						state;
	int						is_linked;
	struct s_entity_list	*next;
}					t_entity_list;

typedef struct s_sector_list
{
	t_editor_walls	*walls;
	t_editor_light	light;
	unsigned char	*sector_plot;
	int				nb_of_walls;
	int				idx_sector;
	int				tex_floor;
	int				tex_ceil;
	int				is_elevator;
	int				has_light_button;
	int				has_light_source;
	t_box					bbox;
	struct s_sector_list	*next;
}					t_sector_list;

typedef struct s_editor
{
	t_sector_list		*sector_list;
	t_entity_list		*entity_list;
	t_button			**button_list;
	t_entity_list		*temp_entity;
	t_sector_list		*temp_sector;
	t_editor_walls		*temp_wall;
	char				**map_names;
	t_mouse_data		mouse_data;
	t_buffer			buffer;
	t_window			win;
	t_action			action;
	t_plr_pos			plr;
	int					grid_size;
	int					end_sector;
	unsigned char		*mapname;
	unsigned char		*linked_mapname;
}					t_editor;

// SDL DRAWING STUFF
void			launch_editor(t_home *home, SDL_Event *e);

/*
** Rendering/drawing
*/

void			draw_ui(t_editor *editor);
void			draw_buttons(t_button **blist, t_buffer *buffer, int draw_depth, t_action *action, int end_sector);
void			draw_sector_textfields(t_sector_list *sector, t_buffer *buffer);

/*
** Buttons
*/

t_button		**create_button_list(t_button **blist);
void			main_button_actions(t_action *action, int i);
void			entity_button_actions(t_action *action, int i);
void			wall_button_actions(t_action *action, int i);
void			sector_button_actions(t_action *action, int i);
int				check_bbox(t_xy start, t_xy end, int mouse_x, int mouse_y);

/*
** Event handler and event related
*/

void			check_event(t_mouse_data *mouse_data, t_button **list,
				t_action *action);
void			editor_events(SDL_Event *e, t_home *home, t_editor *editor);
void			mouse_zoom(t_action *action, int mouse_x, int mouse_y,
				int zoom);
int				handle_events(t_editor *editor, t_home *home);
void			reset_actions(t_action *action);
void			new_check_event(t_editor *editor);
void			unlink_selected_entity(t_entity_list **list, int entity_idx,
				int *unlink_state);
void			check_ui_events(int x, int y, t_button ***blist,
				t_action *action);
int				clicked_inside_grid(int x, int y, int height, int width);
int				check_plr_start_and_end_sector_exists(
				t_sector_list **list, t_plr_pos plr, int end_sector);
void			assign_end_sector(t_sector_list **list, t_screen_xy *mdata,
				int *end_sector, int *sector_assigned);
int				assign_player_start(t_sector_list **list,
				t_screen_xy *mdata, t_plr_pos *plr, int *assign_player_start);
t_sector_list	*get_clicked_sector(t_sector_list **list,
				t_screen_xy mdata, int *selected_sector);
t_editor_walls	*get_clicked_wall(t_editor_walls **walls, t_screen_xy mdata,
				int *selected_wall, int nbr_of_walls);
void			check_grid_events(t_editor *editor);
void			link_maps(t_action *action, unsigned char **linked_mapname,
				char **map_names);
int				clicked_inside_ui(int x, int y, int height, int width);

/*
**				Wall creation.
*/
t_editor_walls	*new_wall_point(t_screen_xy world_coord);
void			add_point_end(t_editor_walls **point, t_editor_walls *new);
int				add_point_to_list(t_sector_list *sector, t_mouse_data *data,
					t_action *action);
void			close_editor_wall_list(t_editor_walls **head);

/*
**				Validity checks
*/

void			close_editor_wall_list(t_editor_walls **head);
void			remove_last_point(t_editor_walls **walls, int *nb_of_walls,
				int selected_point);
int				check_for_last_point(t_sector_list *sector, t_mouse_data *data,
				t_action *action);
int				check_for_intersecting_lines(t_sector_list *sector,
				t_screen_xy p0, t_screen_xy p1);
int				check_if_non_convex(t_sector_list *sector);
/*
** Entities
*/

void			create_new_entity(t_entity_list **head, t_mouse_data *mdata, t_action *action, t_sector_list *sector);
void			delete_selected_entity(t_entity_list **head, t_action *action);
unsigned int	get_entity_count(t_entity_list **list);
t_entity_list	*get_selected_entity(t_entity_list **head, t_mouse_data	mdata);
t_entity_list	*get_clicked_entity(t_entity_list **list, t_screen_xy mdata, int *selected_entity);
int				link_entities(t_entity_list **list, t_screen_xy mdata, int current_entity);
void			edit_entity(t_entity_list *entity, t_action *action);
void			free_all_entities(t_entity_list **head);

/*
** Sector creation and manipulation
*/

void			create_new_sector(t_sector_list **head, t_action *action);
int				handle_sector(t_sector_list **head, t_mouse_data *mouse_data, t_action *action);
void			edit_story(t_sector_list *sector, t_action *action);


void			editor_free_walls(t_editor_walls **head, int nbr_of_walls);
void			editor_free_sector(t_sector_list **head);
void			editor_free_selected_sector(t_sector_list **head, t_entity_list **entity_head, t_action *action);


/*
** Editor map loading stuff
*/
t_xy			get_ndc(t_buffer *buffer, t_screen_xy coord);
void			init_actions(t_action *action);
void			init_mouse_data(t_mouse_data *mouse_data);

void			editor_load_map(t_editor *editor);
void			load_map_names_to_memory(t_editor *editor);
void			editor_free_all_sectors(t_sector_list **head);
void			assign_sector_bbox(t_sector_list *sector);

int				check_saving_prerequisites(t_editor *editor);
void			save_editor_map(t_editor *editor, t_home *home);
void			read_input_string(unsigned char **string, t_action *action);
unsigned char	*delete_char_from_string(unsigned char **string);
t_xy			world_to_screen(t_screen_xy x0, float scalarf, t_xy offsetf,
					t_buffer *buffer);
t_xy			ndc_to_world(t_xy ndc, t_xy offset, float scalar);
#endif

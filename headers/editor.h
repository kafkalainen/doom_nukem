/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:29:25 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/11 11:33:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# define TOOLBAR_WIDTH 300

enum e_menu_state
{
	idle,
	allocate,
	user_input
};

enum e_buttons
{
	button_save,
	button_open,
	button_activate_grid,
	button_create_sector,
	button_assign_end_sector,
	button_link_map,
	button_unlink_map,
	button_plr_start,
	button_create_elevator,
	button_edit_sector,
	button_change_floor_tex,
	button_change_ceil_tex,
	button_set_light_intensity,
	button_is_elevator,
	button_create_light_src,
	button_input_active,
	button_add_wall_point,
	button_wall_index,
	button_change_wall_tex,
	button_convert_to_portal,
	button_set_ceiling_height,
	button_set_floor_height,
	button_create_light_button,
	button_create_powerstation,
	button_entity_index,
	button_change_entity_type,
	button_toggle_entity_is_linked,
	button_toggle_is_revealed,
	button_toggle_is_static,
	button_toggle_state,
};

typedef struct s_mouse_data
{
	int						x;
	int						y;
	float					x_rel;
	float					y_rel;
	int						selected;
	int						i_mbleft;
	int						i_mbright;
}						t_mouse_data;

typedef struct s_editor_walls
{
	t_screen_xy				x0;
	t_screen_xy				norm;
	t_xy					centroid_vec;
	t_height				height;
	t_box					bbox;
	float					center_angle;
	float					dist_from_center;
	int						idx;
	int						type;
	struct s_editor_walls	*next;
}				t_editor_walls;

/*
**	intensity between 0-100, can be rescaled on gamesetup between 0-1
*/

typedef struct s_editor_light
{
	t_screen_xy		pos;
	int				intensity;
	int				is_linked;
	int				state;
}				t_editor_light;

typedef struct s_button_info
{
	char			*text;
	int				inputfield;
	int				draw_depth;
}						t_button_info;

typedef struct s_button
{
	t_button_info	info;
	t_xy			ltop;
	t_xy			wh;
}					t_button;

typedef struct s_plr_pos
{
	int				x;
	int				z;
	int				sector;
}					t_plr_pos;

typedef struct s_action
{
	t_xy			offsetf;
	t_xy			mouse_pos;
	t_xy			world_pos;
	int				grid;
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
	int				write_sector_story;
}					t_action;

typedef struct s_editor_xyz
{
	int						x;
	int						y;
	int						z;
}					t_editor_xyz;

typedef struct s_entity_list
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

typedef struct s_editor_sector
{
	t_editor_walls			*walls;
	t_editor_light			light;
	t_box					bbox;
	t_xy					centroid;
	unsigned char			*sector_plot;
	int						nb_of_walls;
	int						idx_sector;
	int						tex_floor;
	int						tex_ceil;
	int						is_elevator;
	int						has_light_button;
	int						has_light_source;
	struct s_editor_sector	*next;
}					t_editor_sector;

typedef struct s_editor
{
	t_editor_sector			*sector_list;
	t_entity_list			*entity_list;
	t_button				**button_list;
	t_entity_list			*temp_entity;
	t_editor_sector			*temp_sector;
	t_editor_walls			*temp_wall;
	char					**map_names;
	unsigned char			*int_string;
	unsigned char			*mapname;
	unsigned char			*linked_mapname;
	t_mouse_data			mouse_data;
	t_buffer				buffer;
	t_window				win;
	t_action				action;
	t_plr_pos				plr;
	int						grid_size;
	int						end_sector;

}					t_editor;

// SDL DRAWING STUFF
void			launch_editor(t_home *home, SDL_Event *e);

/*
** Rendering/drawing
*/

void			draw_ui(t_editor *editor, t_texture **textures);

/*
** Buttons
*/

t_button		**create_button_list(t_button **blist);
void			main_button_actions(t_action *action, int i);
void			entity_button_actions(t_action *action, int i);
void			wall_button_actions(t_action *action, int i);
void			sector_button_actions(t_action *action, int i);
t_bool			check_bbox(t_xy start, t_xy end, t_xy click);
t_bool			check_bbox_ui(t_xy start, t_xy end, t_xy click);
t_bool			check_if_another_sector_is_inside(t_editor_sector *tested,
					t_editor_sector **head);

/*
** Event handler and event related
*/

void			check_event(t_mouse_data *mouse_data, t_button **list,
					t_action *action);
void			editor_events(SDL_Event *e, t_home *home, t_editor *editor);
void			mouse_zoom(t_action *action, int zoom);
int				handle_events(t_editor *editor, t_home *home);
void			reset_actions(t_action *action);
void			new_check_event(t_editor *editor);
void			unlink_selected_entity(t_entity_list **list, int entity_idx,
					int *unlink_state);
void			check_ui_events(int x, int y, t_button ***blist,
					t_action *action);
int				clicked_inside_grid(int x, int y, int height, int width);
int				check_plr_start_and_end_sector_exists(
					t_editor_sector **list, t_plr_pos plr, int end_sector);
void			assign_end_sector(t_editor_sector **list, t_xy *click,
					int *end_sector, int *sector_assigned);
int				assign_player_start(t_editor_sector **list, t_xy *click,
					t_plr_pos *plr, int *assign_player_start);
t_editor_sector	*get_clicked_sector(t_editor_sector **list,
					t_xy click, int *selected_sector);
t_editor_walls	*get_clicked_wall(t_editor_walls **walls, t_xy click,
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
int				add_point_to_list(t_editor_sector **head, t_editor_sector *sector,
					t_action *action);
void			close_editor_wall_list(t_editor_walls **head);

/*
**				Validity checks
*/
void			close_editor_wall_list(t_editor_walls **head);
void			remove_last_point(t_editor_walls **walls, int *nb_of_walls,
					int selected_point);
int				check_for_last_point(t_editor_sector *sector, t_action *action);
t_bool			check_for_intersecting_lines(t_editor_sector *sector,
					t_screen_xy p0, t_screen_xy p1);
t_bool			check_all_sectors_for_intersecting_lines(t_editor_sector **head,
					t_screen_xy p0, t_screen_xy p1);
int				check_if_non_convex(t_editor_sector *sector);
t_bool			editor_check_if_same_point(t_screen_xy p0, t_screen_xy p1);
int				editor_orientation_of_three_points(t_screen_xy a,
					t_screen_xy b, t_screen_xy c);
t_bool			editor_get_scalar_to_intersection(t_screen_xy pos, t_screen_xy dir,
					t_editor_walls *wall, float *t);

/*
** Entities
*/

void			create_new_entity(t_entity_list **head,
					t_action *action, t_editor_sector *sector);
int				editor_parse_entity_data(t_editor *editor, unsigned char *buf,
					ssize_t size);
void			delete_selected_entity(t_entity_list **head, t_action *action);
unsigned int	get_entity_count(t_entity_list **list);
t_entity_list	*get_selected_entity(t_entity_list **head, t_mouse_data	mdata);
t_entity_list	*get_clicked_entity(t_entity_list **list, t_xy click,
					int *selected_entity);
int				link_entities(t_entity_list **list, t_xy click,
					int current_entity);
void			edit_entity(t_entity_list *entity, t_action *action);
void			free_all_entities(t_entity_list **head);

/*
** Sector creation and manipulation
*/

t_xy			calculate_centroid(t_editor_sector *sector);
void			editor_create_new_sector(t_editor_sector **head,
				t_action *action);
int				editor_new_sector_wallpoints(t_editor_sector **head,
					t_mouse_data *mouse_data, t_action *action);
void			editor_sort_wall_vertices(t_editor_sector *sector);
void			editor_free_walls(t_editor_walls **head, int nbr_of_walls);
void			editor_free_sector(t_editor_sector **head);
void			editor_free_selected_sector(t_editor_sector **head,
					t_entity_list **entity_head, t_action *action);

/*
** Editor map loading stuff
*/

t_xy			get_ndc(t_buffer *buffer, t_screen_xy coord);
void			init_actions(t_action *action);
void			init_mouse_data(t_mouse_data *mouse_data);

void			editor_load_map(t_editor *editor);
void			load_map_names_to_memory(t_editor *editor);
void			editor_free_all_sectors(t_editor_sector **head);
void			assign_sector_bbox(t_editor_sector *sector);

int				check_saving_prerequisites(t_editor *editor);
void			save_editor_map(t_editor *editor, t_home *home);
void			read_input_string(unsigned char **string, t_action *action);
unsigned char	*delete_char_from_string(unsigned char **string);
t_xy			world_to_screen(t_xy x0, float scalarf, t_xy offsetf,
					t_buffer *buffer);
t_xy			ndc_to_world(t_xy ndc, t_xy offset, float scalar);
float			ft_roundf_to_grid(float nb, int prec);
int				editor_select_entity_tex(Uint32 type);
void			free_walls(t_editor_walls **head, int nbr_of_walls);

int				editor_get_sector_data(unsigned char *buf,
				unsigned int *pos, ssize_t size, t_editor_sector **head);
void			reload_editor_with_defaults(t_editor *editor, char *path);
int				editor_parse_map_name(t_editor *editor, ssize_t size,
				unsigned char *buf, unsigned int **pos);
int				editor_get_map_header(unsigned int *pos, unsigned char *buf,
				t_editor *editor, ssize_t size);
int				editor_get_player_position(unsigned int *pos,
				unsigned char *buf, t_plr_pos *plr, ssize_t size);
int				editor_parse_vertex_data(t_editor_sector *new,
				unsigned char *buf, unsigned int *pos, ssize_t size);
t_editor_walls	*editor_new_point(t_point_data *data);
int				editor_parse_coordinates(t_point_data *data,
				unsigned int ***pos, unsigned char **buf, ssize_t size);
int				editor_add_points(t_editor_sector *sector,
				unsigned char *buf, unsigned int **pos, ssize_t size);
int				editor_parse_light_data(t_editor_sector *new,
				unsigned char *buf, unsigned int *pos, ssize_t size);
char			*editor_get_next_string(unsigned char *buf,
				unsigned int **pos, ssize_t size);
int				editor_parse_story_data(t_editor_sector *new,
				unsigned char *buf, unsigned int *pos, ssize_t size);
int				editor_parse_sector_data(t_editor *editor, unsigned char *buf,
				ssize_t size);
int				editor_check_entity_data_header(unsigned char **buf,
				unsigned int *pos, ssize_t size);
int				editor_get_entity_data(unsigned char *buf,
				t_entity_list *entity, unsigned int *pos, ssize_t size);

#endif

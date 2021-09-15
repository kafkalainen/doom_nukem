/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_entities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:28:47 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 08:41:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	editor_select_entity_tex(Uint32 type)
{
	if (type == skull_skulker)
		return (-enemy0);
	else if (type == thing)
		return (-enemy1);
	else if (type == lift_button)
		return (-button_on);
	else if (type == light_button)
		return (-button_on);
	else if (type == powerstation)
		return (-power_station_ready);
	else if (type == lamp)
		return (-lamp_on);
	else if (type == ammo_pack)
		return (-ammo_pack_sprite);
	else if (type == keycard_engineering)
		return (-engineering_keycard_sprite);
	else if (type == keycard_cleaning)
		return (-cleaning_keycard_sprite);
	else if (type == keycard_military)
		return (-military_keycard_sprite);
	return (-enemy0);
}

static void	draw_entity_bbox(t_entity_list *entity, t_editor *editor,
			t_texture **textures)
{
	t_box	box;
	Uint32	color;
	t_texel	*tex;
	float	scale;

	tex = get_tex(editor_select_entity_tex(entity->entity_type), textures);
	box.start = world_to_screen(entity->bbox.start, editor->action.scalarf,
				editor->action.offsetf, &editor->buffer);
	box.end = world_to_screen(entity->bbox.end, editor->action.scalarf,
				editor->action.offsetf, &editor->buffer);
	scale = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
	if (entity->entity_idx == editor->action.selected_entity)
		color = get_color(white);
	else
		color = get_color(red);
	draw_box(box, &editor->buffer, color);
	draw_image(box.start, tex, &editor->buffer, scale);
}

void	draw_editor_entities(t_editor *editor, t_texture **textures)
{
	t_entity_list	*temp;
	t_entity_list	*head;

	head = editor->entity_list;
	temp = editor->entity_list;
	while (temp != NULL)
	{
		draw_entity_bbox(temp, editor, textures);
		// draw_entity_links(temp, editor);
		// if (temp->is_linked)
		// {
		// 	while (link != NULL)
		// 	{
		// 		if (link->is_linked == temp->is_linked && link->is_linked > 1)
		// 			draw_line(
		// 				world_to_screen(vec2(temp->pos.x, temp->pos.z), editor->action.scalarf, editor->action.offsetf,
		// 					&editor->buffer),
		// 				world_to_screen(vec2(link->pos.x, link->pos.z), editor->action.scalarf, editor->action.offsetf,
		// 					&editor->buffer),
		// 				get_color(blue), &editor->buffer);
		// 		link = link->next;
		// 	}
		// 	link = head;
		// }
		temp = temp->next;
	}
	editor->entity_list = head;
}

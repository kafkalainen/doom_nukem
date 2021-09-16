/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_entities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:28:47 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/16 14:50:19 by jnivala          ###   ########.fr       */
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

void	draw_image_static(t_xy offset, t_texel *tex, t_buffer *buffer,
		float scale)
{
	t_pxl_coords	cur;
	t_pxl_coords	image;
	t_uvz			txl;
	t_uv			cur_texel;

	cur = (t_pxl_coords){0, 0};
	image = (t_pxl_coords){tex->height * scale, tex->width * scale};
	txl = (t_uvz){0.0f, 0.0f, 1.0f};
	scale = 1.0f / (tex->height * scale);
	while (cur.y < image.y)
	{
		cur.x = 0;
		txl.u = 0.0f;
		while (cur.x < image.x)
		{
			cur_texel = (t_uv){txl.u * (tex->width - 1),
				txl.v * (tex->height - 1)};
			put_pixel(buffer, (t_pxl_coords){cur.x + offset.x,
				cur.y + offset.y},
				tex->texels[cur_texel.v * tex->width + cur_texel.u]);
			txl.u += scale;
			cur.x++;
		}
		txl.v += scale;
		cur.y++;
	}
}

static void	draw_entity_bbox(t_entity_list *entity, t_editor *editor,
			t_texture **textures)
{
	t_box			box;
	Uint32			color;
	t_texel			*tex;
	float			scale;

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
	draw_image_static(box.start, tex, &editor->buffer, scale);
}

void	draw_editor_entities(t_editor *editor, t_texture **textures)
{
	t_entity_list	*temp;

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
}

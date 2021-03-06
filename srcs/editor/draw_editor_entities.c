/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_entities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:28:47 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/11 10:13:34 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	editor_select_entity_tex_two(t_uint type)
{
	if (type == poster)
		return (-poster_whole);
	return (-enemy0);
}

int	editor_select_entity_tex(t_uint type, t_bool is_revealed)
{
	if (type == skull_skulker && is_revealed == false)
		return (-enemy0);
	else if (type == skull_skulker && is_revealed == true)
		return (-enemy0);
	else if (type == thing && is_revealed == false)
		return (-enemy1);
	else if (type == thing && is_revealed == true)
		return (-enemy3);
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
	return (editor_select_entity_tex_two(type));
}

void	draw_image_static(t_xy offset, t_texel *tex, t_buffer *buffer,
		float scale)
{
	t_pxl_coords	cur;
	t_pxl_coords	image;
	t_uvz			txl;
	t_uv			cur_texel;

	cur = (t_pxl_coords){0, 0};
	image = (t_pxl_coords){tex->width * scale, tex->height * scale};
	txl = (t_uvz){0.0f, 0.0f, 1.0f};
	scale = 1.0f / (tex->width * scale);
	while (cur.y < image.y && txl.v < 1.0f)
	{
		cur.x = -1;
		txl.u = 0.0f;
		while (++cur.x < image.x && txl.u < 1.0f)
		{
			cur_texel = (t_uv){txl.u * (tex->width - 1),
				txl.v * (tex->height - 1)};
			put_pixel(buffer, (t_pxl_coords){cur.x + offset.x,
				cur.y + offset.y},
				tex->texels[cur_texel.v * tex->width + cur_texel.u]);
			txl.u += scale;
		}
		txl.v += scale;
		cur.y++;
	}
}

static void	draw_entity_bbox(t_entity_list *entity, t_editor *editor,
			t_texture **textures)
{
	t_box			box;
	Uint32			colour;
	t_texel			*tex;
	t_xy			scale;

	tex = get_tex(editor_select_entity_tex(entity->type, entity->is_revealed),
			textures);
	box.start = world_to_screen(entity->bbox.start, editor->action.scalarf,
			editor->action.offsetf, &editor->buffer);
	box.end = world_to_screen(entity->bbox.end, editor->action.scalarf,
			editor->action.offsetf, &editor->buffer);
	colour = get_entity_colour(entity, editor->action.selected_entity);
	draw_box(box, &editor->buffer, colour);
	if (is_enemy(entity->type))
	{
		scale = (t_xy){SMALL_ENEMY, SMALL_ENEMY,
			(float)(ft_fabsf(box.end.x - box.start.x) / SMALL_ENEMY)};
		draw_multisprite_image(box.start, tex, &editor->buffer, scale);
	}
	else
	{
		scale.w = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
		draw_image_static(box.start, tex, &editor->buffer, scale.w);
	}
}

void	draw_editor_entities(t_editor *editor, t_texture **textures)
{
	t_entity_list	*temp;

	temp = editor->entity_list;
	while (temp != NULL)
	{
		draw_entity_bbox(temp, editor, textures);
		draw_editor_entity_links(temp, editor);
		temp = temp->next;
	}
}

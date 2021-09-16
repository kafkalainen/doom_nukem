/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_another_sector_is_inside.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:45:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/16 11:39:49 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// // DEBUGGING
// static void		print_point(t_screen_xy point, char *str)
// {
// 	ft_putendl(str);
// 	ft_putstr("x: ");
// 	ft_putnbr(point.x);
// 	ft_putstr(" y: ");
// 	ft_putnbr(point.y);
// 	ft_putchar('\n');
// }

static t_bool	check_point_is_on_bbox_line(t_editor_walls *wall,
				t_box *box)
{
	t_screen_xy	top_left;
	t_screen_xy	top_right;
	t_screen_xy	bot_left;
	t_screen_xy	bot_right;

	top_left = round_coordinates(vec2(box->start.x, box->start.y));
	top_right = round_coordinates(vec2(box->end.x, box->start.y));
	bot_left = round_coordinates(vec2(box->start.x, box->end.y));
	bot_right = round_coordinates(vec2(box->end.x, box->end.y));
	if (editor_point_is_on_the_lseg(top_left, wall->x0, top_right))
		return (true);
	if (editor_point_is_on_the_lseg(top_right, wall->x0, bot_right))
		return (true);
	if (editor_point_is_on_the_lseg(bot_right, wall->x0, bot_left))
		return (true);
	if (editor_point_is_on_the_lseg(bot_left, wall->x0, top_left))
		return (true);
	if (editor_check_if_same_point(top_left, wall->x0)
		|| editor_check_if_same_point(top_right, wall->x0)
		|| editor_check_if_same_point(bot_left, wall->x0)
		|| editor_check_if_same_point(bot_right, wall->x0))
		return (true);
	return (false);
}

t_bool	check_if_another_sector_is_inside(t_editor_sector *tested,
		t_editor_sector **head)
{
	int				i;
	t_editor_walls	*cur_wall;
	t_editor_sector	*temp;
	t_editor_sector	*original_head;

	temp = *head;
	original_head = *head;
	while (temp->next)
	{
		i = 0;
		cur_wall = temp->walls;
		while (i < temp->nb_of_walls)
		{
			if (check_bbox(tested->bbox.start, tested->bbox.end,
					vec2(cur_wall->x0.x, cur_wall->x0.y))
				&& !check_point_is_on_bbox_line(cur_wall,
					&tested->bbox))
				return (true);
			cur_wall = cur_wall->next;
			i++;
		}
		temp = temp->next;
	}
	temp = original_head;
	return (false);
}

t_bool	check_if_completely_inside(t_editor_sector *tested,
		t_editor_sector **head)
{
	int				i;
	int				points_inside;
	t_editor_walls	*cur_wall;
	t_editor_sector	*temp;

	temp = *head;
	while (temp->next)
	{
		i = 0;
		points_inside = 0;
		cur_wall = tested->walls;
		while (i < tested->nb_of_walls)
		{
			if (check_bbox(temp->bbox.start, temp->bbox.end,
					vec2(cur_wall->x0.x, cur_wall->x0.y)))
				points_inside++;
			cur_wall = cur_wall->next;
			i++;
		}
		if (points_inside >= tested->nb_of_walls)
			return (true);
		temp = temp->next;
	}
	return (false);
}

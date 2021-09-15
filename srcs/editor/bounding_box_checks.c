/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:46:37 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/15 16:48:30 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_bbox(t_xy start, t_xy end, t_xy click)
{
	if (start.x <= click.x && start.y >= click.y
		&& end.x >= click.x && end.y <= click.y)
		return (true);
	else
		return (false);
}

t_bool	check_bbox_ui(t_xy start, t_xy end, t_xy click)
{
	if (start.x <= click.x && start.y <= click.y
		&& end.x >= click.x && end.y >= click.y)
		return (true);
	else
		return (false);
}

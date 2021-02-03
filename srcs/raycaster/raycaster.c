#include "../../doom_nukem.h"

t_ray_fov			get_fov_points(t_point *plgn, t_home *home, t_player *plr, int i)
{
	t_ray_fov		ray;
	t_intersection	sect[2];

	ray.ray_left.pos = plr->pos;
	ray.ray_right.pos = plr->pos;
	ray.ray_left.dir = vec2_rot(plr->dir, DEG_TO_RAD * -FOV * 0.5);
	ray.ray_right.dir = vec2_rot(plr->dir, DEG_TO_RAD * FOV * 0.5);
	calc_intersection(plgn, home->sectors[i]->points, &ray.ray_left, &sect[0]);
	calc_intersection(plgn, home->sectors[i]->points, &ray.ray_right, &sect[1]);
	ray.left_point = line_intersection(&sect[0]);
	ray.right_point = line_intersection(&sect[1]);
	return (ray);
}

t_xy		line_intersection(t_intersection *sect)
{
	t_xy point;

	if (sect->neg > 0 && sect->neg < 1 && sect->pos > 0)
	{
		point.x = (sect->x1 + sect->neg * (sect->x2 - sect->x1));
		point.y = (sect->y1 + sect->neg * (sect->y2 - sect->y1));
		return (point);
	}
	return (vec2(-1, -1));
}

void		calc_intersection(t_point *pgon, t_point *first, t_ray *ray,
					t_intersection *sect)
{
	// t_point		*temp;

	sect->y1 = pgon->x0.y;
	sect->x1 = pgon->x0.x;
	// temp = loop_list(first, pgon->next);
	// sect->x2 = temp->x0.x;
	// sect->y2 = temp->x0.x;
	if (pgon->next == NULL)
	{
		sect->x2 = first->x0.x;
		sect->y2 = first->x0.y;
	}
	else
	{
		sect->x2 = pgon->next->x0.x;
		sect->y2 = pgon->next->x0.y;
	}
	sect->neg = ((sect->x1 - ray->pos.x) * (-ray->dir.y) - (sect->y1 - ray->pos.y) *
				(-ray->dir.x));
	sect->pos = ((sect->x2 - sect->x1) * (sect->y1 - ray->pos.y) -
				(sect->y2 - sect->y1) * (sect->x1 - ray->pos.x));
	if ((sect->pos < 0 && sect->neg > 0) || (sect->pos > 0 && sect->neg < 0))
		return ;
	sect->den = ((sect->x1 - sect->x2) * (-ray->dir.y) -
				(sect->y1 - sect->y2) * (-ray->dir.x));
	sect->neg /= sect->den;
	sect->pos /= sect->den;
}

// void			get_max_points(t_home *home, t_player *plr, t_intersection *sect)
// {
// 	int i;
// 	t_point	*current;
// 	t_point	*next;
// 	t_maxpoints	max;
// 	t_ray_fov	fov;

// 	i = 0;
// 	while(i < 2)
// 	{
// 		current = home->sectors[i]->points;
// 		while (current)
// 		{
// 			if (current->idx)
// 			{
// 				next = (current->next == NULL) ? home->sectors[i]->points : current->next;
// 				fov = get_fov_points(current, home, plr, i);
// 				if (fov.left_point.x > 0)
// 					max.left = fov.left_point;
// 				if (fov.right_point.x > 0)
// 					max.right = fov.right_point;
// 			}
// 			if (current->next == NULL)
// 				break ;
// 			current = current->next;
// 		}
// 		i++;
// 	}
// }

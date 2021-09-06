#include "../../headers/doom_nukem.h"

t_xy	line_intersection(t_intersection *sect)
{
	t_xy	point;

	if (sect->neg > 0 && sect->neg <= 1 && sect->pos > 0)
	{
		point.x = (sect->x1 + sect->neg * (sect->x2 - sect->x1));
		point.y = (sect->y1 + sect->neg * (sect->y2 - sect->y1));
		return (point);
	}
	return (vec2(-1, -1));
}

void	calc_intersection(t_wall *wall, t_ray *ray, t_intersection *sect)
{
	sect->y1 = wall->top.p[1].z;
	sect->x1 = wall->top.p[1].x;
	sect->y2 = wall->top.p[2].z;
	sect->x2 = wall->top.p[2].x;
	sect->neg = ((sect->x1 - ray->pos.x) * (-ray->dir.y)
			- (sect->y1 - ray->pos.y) * (-ray->dir.x));
	sect->pos = ((sect->x2 - sect->x1) * (sect->y1 - ray->pos.y)
			- (sect->y2 - sect->y1) * (sect->x1 - ray->pos.x));
	if (sect->pos >= 0.0f && sect->pos <= 1.0f
		&& sect->neg >= 0.0f && sect->neg <= 1.0f)
		return ;
	sect->den = ((sect->x1 - sect->x2) * (-ray->dir.y)
			- (sect->y1 - sect->y2) * (-ray->dir.x));
	if (sect->den == 0)
		return ;
	sect->neg /= sect->den;
	sect->pos /= sect->den;
}

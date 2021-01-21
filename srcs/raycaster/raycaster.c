#include "../../doom_nukem.h"

t_xy		line_intersection(t_intersection *sect)
{
	t_xy point;
	
	if (sect->neg > 0 && sect->neg < 1 && sect->pos > 0)
	{
		point.x = (sect->x1 + sect->neg * (sect->x2 - sect->x1));
		point.y = (sect->y1 + sect->neg * (sect->y2 - sect->y1));
	}
	return (point);
}

void		calc_intersection(t_polygon *pgon, t_xy *pos, t_xy *dir, 
					t_intersection *sect)
{
	sect->x1 = pgon->x0.x;
	sect->x2 = pgon->next->x0.x;
	sect->y1 = pgon->x0.y;
	sect->y2 = pgon->next->x0.y;

	sect->den = ((sect->x1 - sect->x2) * (-dir->y) - 
				(sect->y1 - sect->y2) * (-dir->x));
	sect->neg = ((sect->x1 - pos->x) * (-dir->y) - (sect->y1 - pos->y) *
				(-dir->x)) / sect->den;
	sect->pos = -((sect->x1 - sect->x2) * (sect->y1 - pos->y) -
				(sect->x1 - pos->x)) / sect->den;
}
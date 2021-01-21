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

void		calc_intersection(t_polygon *pgon, t_polygon *first, t_player *plr, 
					t_intersection *sect)
{
	sect->y1 = pgon->x0.y;
	sect->x1 = pgon->x0.x;
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
	sect->den = ((sect->x1 - sect->x2) * (-plr->dir.y) - 
				(sect->y1 - sect->y2) * (-plr->dir.x));
	sect->neg = ((sect->x1 - plr->pos.x) * (-plr->dir.y) - (sect->y1 - plr->pos.y) *
				(-plr->dir.x)) / sect->den;
	sect->pos = ((sect->x2 - sect->x1) * (sect->y1 - plr->pos.y) -
				(sect->y2 - sect->y1) * (sect->x1 - plr->pos.x)) / sect->den;
}

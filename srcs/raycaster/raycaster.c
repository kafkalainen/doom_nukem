#include "doom_nukem.h"

static int		cast(t_xy *pos, t_xy *dir, t_polygon *polygons)
{
	float x1 = polygons->x0.x;
	float y1 = polygons->x0.y;
	float x2 = polygons->next->x0.x;
	float y2 = polygons->next->x0.y;

	float x3 = pos->x;
	float y3 = pos->y;
	float x4 = pos->x + dir->x;
	float y4 = pos->y + dir->y;

	float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0)
		return (0);
	float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	float u = -((x1 - x2) * (y1- y3) - (y1 - y2) * (x1 - x3)) / den;
	if (t > 0 && t < 1 && u > 0)
		return (1);
	else
		return (-1);
}
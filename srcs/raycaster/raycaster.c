#include "doom_nukem.h"

static int		cast(t_ray ray, t_line line)
{
	double x1 = line.start.x;
	double y1 = line.start.y;
	double x2 = line.end.x;
	double y2 = line.end.y;

	double x3 = ray.pos.x;
	double y3 = ray.pos.y;
	double x4 = ray.pos.x + ray.dir.x;
	double y4 = ray.pos.y + ray.dir.y;

	double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0)
		return (0);
	double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	double u = -((x1 - x2) * (y1- y3) - (y1 - y2) * (x1 - x3)) / den;
	if (t > 0 && t < 1 && u > 0)
		return (1);
	else
		return (-1);
}
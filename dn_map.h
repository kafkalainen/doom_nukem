#include "doom_nukem.h"

typedef struct		s_enemy
{
	int				hp;
}					t_enemy;

typedef struct		s_polygon
{
	t_xy			x0;
	t_xy			normal;
	int				idx_tex;
	int				connection;
}					t_polygon;

typedef struct		s_sector
{
	t_polygon		*polygons;
	t_enemy			*enemies;
	int				nb_of_walls;
	int				idx_sector;
	int				tex_floor;
	int				tex_ceil;
	double			ground;
	double			ceiling;
}					t_sector;

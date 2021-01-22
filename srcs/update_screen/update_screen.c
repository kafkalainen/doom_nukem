#include "../../doom_nukem.h"

void	update_screen(t_home *home, t_player *plr)
{
	t_intersection sect;

	//draw_fov(home, plr);
	//draw_minimap(home->map.size, plr->pos, plr->dir, home);
	draw_2d(home, plr, &sect);
}

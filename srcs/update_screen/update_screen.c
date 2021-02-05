#include "../../doom_nukem.h"

void	update_screen(t_home *home, t_frame *frame)
{
	//draw_fov(home, plr);
	//draw_minimap(home->map.size, plr->pos, plr->dir, home);
	draw_2d(home, frame);
}

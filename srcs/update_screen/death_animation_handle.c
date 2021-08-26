//home->game_state = MAIN_MENU;

#include "../../headers/doom_nukem.h"

void		death_animation(t_home *home, t_player *plr, Uint32 t)
{
	plr->pitch= fmin(plr->pitch + 0.002 * t, 89 * DEG_TO_RAD);
	plr->dead += 0.0002 * t;
	if (plr->dead > 2)
		home->game_state = MAIN_MENU;
}

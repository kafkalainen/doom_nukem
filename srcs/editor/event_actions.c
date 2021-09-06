#include "../../headers/doom_nukem.h"

void	mouse_zoom(t_action *action, int mouse_x, int mouse_y, int zoom)
{
	if (zoom)
	{
		action->offset.x *= 2;
		action->offset.y *= 2;
		action->offset.x -= mouse_x;
		action->offset.y -= mouse_y;
		action->scalar *= 2;
	}
	else
	{		
		action->offset.x += mouse_x;
		action->offset.y += mouse_y;
		action->offset.x /= 2;
		action->offset.y /= 2;
		action->scalar /= 2;
	}
}

#include "../../headers/doom_nukem.h"

void	mouse_zoom(t_action *action, int zoom)
{
	if (zoom)
	{
		action->scalarf *= 2.0f;
		action->offsetf.x -= action->mouse_pos.x;
		action->offsetf.y += action->mouse_pos.y;
		action->offsetf.x *= action->scalarf;
		action->offsetf.y *= action->scalarf;
	}
	else
	{
		action->scalarf *= 0.5f;
		action->offsetf.x += action->mouse_pos.x;
		action->offsetf.y -= action->mouse_pos.y;
		action->offsetf.x *= action->scalarf;
		action->offsetf.y *= action->scalarf;
	}
	printf("%f\n", action->scalarf);
}


#include "../headers/doom_nukem.h"

void	create_button(t_button *list, t_xy ltop, t_xy wh, char *text)
{
	list->ltop = ltop;
	list->wh = wh;
	list->text = malloc(sizeof(char) * ft_strlen(text));
	list->text = text;
}

t_button	**create_button_list(t_button **blist)
{
	int i;

	i = 0;
	while (i < NBR_BUTTONS)
		blist[i++] = (t_button*)malloc(sizeof(t_button));
	i = 0;
	create_button(blist[i++], vec2(32, 52), vec2(96, 24), "Print sector data");
	create_button(blist[i++], vec2(32, 80), vec2(96, 24), "Toggle grid");
	create_button(blist[i++], vec2(32, 134), vec2(24, 24), "++");
	create_button(blist[i++], vec2(76, 134), vec2(24, 24), "--");
	create_button(blist[i++], vec2(16, 180), vec2(96, 24), "New sector");
	create_button(blist[i++], vec2(120, 180), vec2(24, 24), "-");
	create_button(blist[i++], vec2(164, 180), vec2(24, 24), "+");
	create_button(blist[i++], vec2(16, 240), vec2(168, 24), "Delete selected sector");
	create_button(blist[i++], vec2(16, 280), vec2(168, 24), "Snap sector to grid");
	create_button(blist[i++], vec2(16, 320), vec2(178, 24), "Show sectors' bboxes");
	create_button(blist[i++], vec2(16, 360), vec2(110, 24), "Sector z:");
	create_button(blist[i++], vec2(16, 390), vec2(110, 24), "Sector height:");
	create_button(blist[i++], vec2(16, 420), vec2(110, 24), "Sector floor tex:");
	create_button(blist[i], vec2(16, 450), vec2(110, 24), "Sector ceiling tex:");
	return(blist);
}

#include "../../headers/doom_nukem.h"

void	edit_story(t_sector_list *sector, t_action *action)
{
	// char	temp;
	char 	c[2];

	if (action->input_active >= 0 && action->keysym >= 48 && action->keysym <= 128)
	{
		c[0] = action->keysym;
		c[1] = '\0';
		// temp = sector->sector_plot;
		if (!sector->sector_plot)
			sector->sector_plot = (unsigned char *)ft_strjoin("#", c);
		else
			sector->sector_plot = (unsigned char *)ft_strjoin((const char *)sector->sector_plot, c);
		action->keysym = -1;
		// free(temp);
	}
}

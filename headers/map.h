#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
	int			num_sectors;
	char		*img_buf;
	char		*audio_buf;
	char		*map_buf[1024];
}				t_map;

#endif

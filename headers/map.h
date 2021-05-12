#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
	int			num_sectors;
	char		*img_buf;
	char		*audio_buf;
	char		*map_buf[1024];
}				t_map;

typedef	struct	s_audio_asset
{
	unsigned int	size;
	unsigned char	*buf;
}				t_audio_asset;

#endif

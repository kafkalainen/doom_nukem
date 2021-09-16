/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:02:59 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/15 16:27:32 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_texture	*get_texture(unsigned char *buf, unsigned int *pos, ssize_t size)
{
	t_png		png;
	int			i;
	int			idx;

	idx = 0;
	i = -1;
	while (++i < 3)
	{
		(*pos) += get_next_breaker(buf + (*pos)) + 1;
		if (*pos > (unsigned int)size)
			error_output("Pointer points outside memory address\n");
		if (i == 0)
			idx = ft_atoi((char *)(buf + (*pos)));
		else if (i == 1)
			png.source.size = ft_atoi((char *)(buf + (*pos)));
		else if (i == 2)
		{
			setup_parser(&png, png.source.size);
			ft_memcpy(png.source.buf, buf + *pos, png.source.size);
			(*pos) += png.source.size;
			if (*pos > (unsigned int)size)
				error_output("Pointer points outside memory address\n");
		}
	}
	return (return_new_texture(&png, idx));
}

t_texture	*assign_empty_texture(void)
{
	t_texture	*tex;

	tex = (t_texture *)malloc(sizeof(t_texture));
	if (!tex)
		error_output("Memory allocation of t_texture struct failed\n");
	tex->source = NULL;
	tex->tex.texels = NULL;
	return (tex);
}

void	parse_texture_data(unsigned char *buf, t_home *home, ssize_t size)
{
	int				i;
	unsigned int	pos;

	pos = 0;
	buf = (unsigned char *)ft_memstr((char *)buf, "#doom_nukem_textures", size);
	pos += get_next_breaker(buf + pos) + 1;
	if (pos > (unsigned int)size)
		error_output("Pointer points outside memory address\n");
	home->textures = (t_texture **)malloc(sizeof(t_texture *) * (NUM_TEX));
	if (!home->textures)
		error_output("failed to allocate memory to editor textures\n");
	home->textures[0] = assign_empty_texture();
	i = 1;
	while (i < (NUM_TEX - 1))
	{
		home->textures[i] = get_texture(buf, &pos, size);
		i++;
	}
	home->textures[i] = assign_empty_texture();
}

void	parse_audio_data(unsigned char *buf, unsigned int *pos,
	char *path, ssize_t size)
{
	t_audio_asset	asset;

	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		error_output("Pointer points outside memory address\n");
	asset.size = ft_atoi((char *)buf + *pos);
	asset.buf = malloc(sizeof(unsigned char *) * asset.size);
	if (!asset.buf)
		error_output("failed to allocate memory to music buffer\n");
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		error_output("Pointer points outside memory address\n");
	ft_memcpy(asset.buf, buf + *pos, asset.size);
	*pos += asset.size;
	if (*pos > (unsigned int)size)
		error_output("Pointer points outside memory address\n");
	if (create_temp_audio_file(asset.buf, asset.size, path) == -1)
		error_output("Failed to create temp audio file\n");
	free(asset.buf);
}

void	parse_map_data(unsigned char *buf, t_player *plr,
	t_home *home, ssize_t size)
{
	int	ret;

	ret = parse_sector_data(buf, plr, home, size);
	ret = parse_entity_data(buf, home, size);
	parse_texture_data(buf, home, size);
	if (doom_mkdir() == -1)
		ft_putstr("ERROR: Failed to create temporary directory.\n");
	parse_all_audio_data(buf, size);
	free(buf);
	buf = NULL;
	if (ret)
		error_output("ERROR: Failed to read map.");
}

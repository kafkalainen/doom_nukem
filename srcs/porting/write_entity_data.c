/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_entity_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:54:41 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/05 14:57:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

unsigned int	get_entity_count(t_entity_list **list)
{
	t_entity_list	*temp;
	unsigned int	i;

	temp = *list;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

/*
**	Parse entity data parses following map data:
**	entity_index
**	entity_type	sector_idx	pos			dir			is_static	is_active
**	#enum entity	int		#x#z#y		#x#z#y		boolean		boolean
**	#4				#2		#0#10#2		#1#0#2		#1			#1
**	#0				#0		#-1#1#2		#1#0#2		#0			#1
**
**	always_facing_plr	is_revealed			state		is_linked
**	boolean				boolean				boolean		Uint32
**	#0					#0					#0			#2
**	#0					#0					#1			#0
*/

unsigned char	*get_writable_entity_data3(t_entity_list *entity,
	unsigned char *buf)
{
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->is_static), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->is_active), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->is_revealed), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->state), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->is_linked), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			"\n", 1, 0);
	return (buf);
}

unsigned char	*get_writable_entity_data2(t_entity_list *entity,
	unsigned char *buf)
{
	buf = (unsigned char *)ft_strjoin_freeable(WRITE_BREAKER,
			ft_itoa(entity->type), 0, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->sector_idx), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->pos.x), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->pos.z), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->pos.y), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->dir.x), 1, 1);
	return (buf);
}

unsigned char	*get_writable_entity_data(t_entity_list *entity)
{
	unsigned char	*buf;

	buf = NULL;
	buf = get_writable_entity_data2(entity, buf);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->dir.z), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(entity->dir.y), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = get_writable_entity_data3(entity, buf);
	return (buf);
}

void	write_entity_data(int *fd, t_editor *editor)
{
	unsigned char	*buf;
	t_entity_list	*temp;

	buf = (unsigned char *)ft_strjoin_freeable("#doom_nukem_entities#",
			ft_itoa(get_entity_count(&editor->entity_list)), 0, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf, "\n", 1, 0);
	if (doom_write(fd, (const void **)&buf, ft_strlen((const char *)buf)) == -1)
		error_output("failed to add entity numbers\n");
	ft_strdel((char **)&buf);
	temp = editor->entity_list;
	while (temp != NULL)
	{
		buf = get_writable_entity_data(temp);
		if (doom_write(fd, (const void **)&buf,
				ft_strlen((const char *)buf)) == -1)
			error_output("failed to add entity data\n");
		ft_strdel((char **)&buf);
		temp = temp->next;
	}
}

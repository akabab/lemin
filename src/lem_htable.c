/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_htable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 10:54:06 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/05 22:06:23 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_htable.h"

t_htable		*htable_create(int size)
{
	t_htable	*htable;
	int			i;

	if (size < 1)
		return (NULL);
	if ((htable = malloc(sizeof(t_htable))) == NULL)
		return (NULL);
	if ((htable->table = malloc(sizeof(t_list_node *) * size)) == NULL)
	{
		free(htable);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		htable->table[i] = NULL;
		i++;
	}
	htable->size = size;
	htable->hash_ft = &hash_sum;
	return (htable);
}

int				htable_add(t_htable *htable, void *data, char *str)
{
	unsigned int	hashval;

	hashval = htable->hash_ft(htable, str);
	list_push_front(&(htable->table[hashval]), data);
	return (0);
}

t_room			*htable_get(t_htable *htable, char *str)
{
	t_list_node		*cursor;
	unsigned int	hashval;
	t_room			*room;

	hashval = htable->hash_ft(htable, str);
	cursor = htable->table[hashval];
	while (cursor)
	{
		room = (t_room *)cursor->value;
		if (ft_strequ((char *)(room->name), str))
			return (room);
		cursor = cursor->next;
	}
	return (NULL);
}

int				htable_count(t_htable *htable)
{
	int				i;
	int				count;
	t_list_node		*cursor;

	count = 0;
	if (!htable)
		return (-1);
	i = 0;
	while (i < htable->size)
	{
		cursor = htable->table[i];
		while (cursor)
		{
			count++;
			cursor = cursor->next;
		}
		i++;
	}
	return (count);
}

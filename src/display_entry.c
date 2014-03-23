/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 21:22:31 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/05 12:40:52 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		display_entry(t_list_node *entry_list)
{
	t_list_node		*cursor;
	t_list_node		*node_to_free;
	char			*line;

	if (!entry_list)
		return ;
	cursor = entry_list;
	while (cursor)
	{
		line = (char *)cursor->value;
		ft_putendl(line);
		node_to_free = cursor;
		cursor = cursor->next;
	}
}

void		free_entry(t_list_node *entry_list)
{
	t_list_node		*cursor;
	t_list_node		*node_to_free;
	char			*line;

	if (!entry_list)
		return ;
	cursor = entry_list;
	while (cursor)
	{
		line = (char *)cursor->value;
		free(line);
		node_to_free = cursor;
		cursor = cursor->next;
		free(node_to_free);
	}
}

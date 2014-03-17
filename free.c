/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 18:02:31 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/17 12:25:06 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		free_path_list(t_list_node *path_list)
{
	t_list_node		*pl_cursor;
	t_list_node		*pr_cursor;
	t_list_node		*pl_node_to_free;
	t_list_node		*pr_node_to_free;
	t_path			*path;

	pl_cursor = path_list;
	while (pl_cursor)
	{
		pl_node_to_free = pl_cursor;
		path = (t_path *)pl_cursor->value;
		pr_cursor = path->room_list;
		while (pr_cursor)
		{
			pr_node_to_free = pr_cursor;
			pr_cursor = pr_cursor->next;
			free(pr_node_to_free);
		}
		free(path);
		pl_cursor = pl_cursor->next;
		free(pl_node_to_free);
	}
}

static void		free_room(t_room *room)
{
	free(room->name);
	list_destroy(&room->adj_list);
	free(room);
}

static void		free_htable(t_htable *htable)
{
	int				i;
	t_list_node		*cursor;
	t_list_node		*node_to_free;

	if (!htable)
		return ;
	i = 0;
	while (i < htable->size)
	{
		cursor = htable->table[i];
		while (cursor)
		{
			free_room((t_room *)cursor->value);
			node_to_free = cursor;
			cursor = cursor->next;
			free(node_to_free);
		}
		i++;
	}
	free(htable->table);
	free(htable);
}

static void		free_entry(t_list_node *entry_list)
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

void			free_memory(t_graph *G)
{
	if (!G)
		return ;
	if (G->entry_list)
		free_entry(G->entry_list);
	if (G->room_ht)
		free_htable(G->room_ht);
	if (G->path_list)
		free_path_list(G->path_list);
	free(G);
}


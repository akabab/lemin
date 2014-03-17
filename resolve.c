/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 11:15:54 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/15 18:30:01 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			uncheck_and_unparent_rooms(t_htable *room_ht)
{
	int				i;
	t_list_node		*room_cursor;
	t_room			*room;

	i = 0;
	while (i < room_ht->size)
	{
		if (room_ht->table[i])
		{
			room_cursor = room_ht->table[i];
			while (room_cursor)
			{
				room = (t_room *)room_cursor->value;
				room->checked = FALSE;
				room->parent = NULL;
				room_cursor = room_cursor->next;
			}
		}
		i++;
	}
}

static void			check_path_rooms(t_graph *G)
{
	t_list_node		*path_list;
	t_path			*path;
	t_list_node		*room_list;
	t_room			*room;

	if (!(path_list = G->path_list))
		return ;
	while (path_list)
	{
		path = (t_path *)path_list->value;
		room_list = path->room_list;
		while (room_list->next)
		{
			room = (t_room *)room_list->value;
			room->checked = TRUE;
			room_list = room_list->next;
		}
		path_list = path_list->next;
	}
}

static t_path		*create_path(t_graph *G)
{
	t_path			*path;
	static uint		path_id = 1;

	if (!(path = malloc(sizeof(t_path))))
		return (NULL);
	path->id = path_id++;
	path->len = -1;
	path->ants = 0;
	path->room_list = NULL;
	path->end = G->end;
	return (path);
}

static int			recover_path(t_graph *G)
{
	t_room					*room;
	t_path					*path;
	static t_list_node		*path_list_end = NULL;

	if (!(path = create_path(G)))
		return (0);
	room = G->end;
	while (room)
	{
		path->len++;
		list_push_front(&(path->room_list), room);
		room = room->parent;
	}
	if (path->id > 1 && path->len >= precalc_cycles(G))
	{
		list_destroy(&(path->room_list));
		free(path);
		return (0);
	}
	if (!G->path_list)
		path_list_end = list_push_back(&(G->path_list), path);
	else
		path_list_end = list_push_back(&path_list_end, path);
	G->total_paths_len += path->len;
	return (1);
}

int					find_paths(t_graph *G)
{
	uint	max_path;
	uint	path_index;

	max_path = ft_min(G->start->n_adj, G->end->n_adj);
	path_index = 0;
	while (path_index < max_path)
	{
		bfs(G);
		if (!G->end->parent)
			break ;
		if (!recover_path(G))
			break ;
		G->n_path += 1;
		uncheck_and_unparent_rooms(G->room_ht);
		check_path_rooms(G);
		path_index++;
	}
	return (path_index);
}

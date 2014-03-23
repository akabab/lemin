/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/07 18:10:02 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/07 18:59:30 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	add_room(t_room *room, t_list_node **queue, t_list_node **queue_end)
{
	t_room				*adj_room;
	t_list_node			*adj_list;

	adj_list = room->adj_list;
	while (adj_list)
	{
		adj_room = (t_room *)adj_list->value;
		if (adj_room->checked == FALSE)
		{
			adj_room->parent = room;
			adj_room->checked = TRUE;
			if (!*queue)
				*queue_end = list_push_back(queue, adj_room);
			else
				*queue_end = list_push_back(queue_end, adj_room);
		}
		adj_list = adj_list->next;
	}
}

void		bfs(t_graph *gr)
{
	t_list_node			*queue;
	t_list_node			*queue_end;
	t_room				*cur_room;

	queue = NULL;
	cur_room = gr->start;
	cur_room->checked = TRUE;
	queue_end = list_push_back(&queue, cur_room);
	while (queue)
	{
		cur_room = list_pop_front(&queue);
		add_room(cur_room, &queue, &queue_end);
	}
}

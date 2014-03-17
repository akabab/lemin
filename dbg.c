/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 18:09:00 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/13 11:11:02 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			display_infos(t_graph *G)
{
	ft_putendl(C(YELLOW)"\n::INFOS::"C(NO));
	ft_printf("Ants: "C(GREEN)"%d\n"C(NO), G->n_ant);
	ft_printf("Rooms: "C(GREEN)"%d\n"C(NO), G->n_room);
	ft_printf("Start room: "C(GREEN)"%s\n"C(NO), G->start->name);
	ft_printf("End room: "C(GREEN)"%s\n"C(NO), G->end->name);
	ft_printf("Paths: "C(GREEN)"%d\n"C(NO), G->n_path);
	ft_printf("Total paths len: "C(GREEN)"%d\n"C(NO), G->total_paths_len);
}

static void		display_adjs(t_room *room)
{
	t_list_node		*adj_cursor;
	t_room			*adj_room;

	adj_cursor = room->adj_list;
	while (adj_cursor)
	{
		adj_room = (t_room *)adj_cursor->value;
		ft_printf(C(PINK)"-[%s]"C(NO), (char *)adj_room->name);
		adj_cursor = adj_cursor->next;
	}
	ft_printf(" {%d}", room->n_adj);
}

void			display_rooms(t_htable *room_ht)
{
	int				i;
	t_list_node		*room_cursor;
	t_room			*room;

	ft_putendl(C(YELLOW)"\n::ROOMS::"C(NO));
	i = 0;
	while (i < room_ht->size)
	{
		if (room_ht->table[i])
		{
			room_cursor = room_ht->table[i];
			while (room_cursor)
			{
				room = (t_room *)room_cursor->value;
				ft_printf(C(GREEN)"[%s]"C(NO), (char *)room->name);
				display_adjs(room);
				ft_putchar('\n');
				room_cursor = room_cursor->next;
			}
		}
		i++;
	}
}

void			print_path(t_path *path)
{
	t_list_node		*room_list;
	t_room			*room;

	ft_printf("id: "C(GREEN)"%d"C(NO), path->id);
	ft_printf(" | len: "C(GREEN)"%d"C(NO), path->len);
	ft_printf(" | ants: "C(GREEN)"%d"C(NO)" --> ", path->ants);
	ft_putstr(C(PINK)"START"C(NO));
	room_list = path->room_list;
	while (room_list)
	{
		room = (t_room *)room_list->value;
		ft_printf(C(GREEN)"-[%s]-"C(NO), room->name);
		room_list = room_list->next;
	}
	ft_putendl(C(PINK)"END"C(NO));
}

void			display_paths(t_graph *G)
{
	t_list_node		*path_list;
	t_path			*path;

	ft_putendl(C(YELLOW)"\n::PATHS::"C(NO));
	if (!(path_list = G->path_list))
	{
		ft_putendl(C(RED)"No path found."C(NO));
		return ;
	}
	while (path_list)
	{
		path = (t_path *)path_list->value;
		print_path(path);
		path_list = path_list->next;
	}
}

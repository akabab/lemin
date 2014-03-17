/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   travel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 12:26:55 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/13 16:47:56 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		print_ant(t_graph *G, uint ant_id, t_room *room)
{
	static uint		current_cycle = -1;

	if (DEBUG)
		ft_putstr(C(NO));
	if (current_cycle == G->n_cycle)
		ft_putchar(' ');
	if (room == G->end && DEBUG && G->debug.ants)
	{
		if (ant_id == G->n_ant)
			ft_putstr(C(PINK));
		else
			ft_putstr(C(GREEN));
	}
	ft_printf("L%d-%s", ant_id, room->name);
	if (DEBUG)
		ft_putstr(C(NO));
	current_cycle = G->n_cycle;
}

static void		push_ants(t_graph *G, t_list_node *room_node, uint *end_ants)
{
	t_room		*room;
	t_room		*next_room;

	room = (t_room *)room_node->value;
	if (room == G->end)
		return ;
	next_room = (t_room *)room_node->next->value;
	push_ants(G, room_node->next, end_ants);
	if (room->ant)
	{
		print_ant(G, room->ant, next_room);
		if (next_room == G->end)
			*end_ants += 1;
	}
	next_room->ant = room->ant;
}

static void		travel_through_path(t_graph *G, t_path *path, uint *end_ants)
{
	t_list_node		*room_list;
	static uint		current_ant_index = 1;
	t_bool			ant_sent;

	if (!path->ants)
	{
		ant_sent = FALSE;
		G->start->ant = 0;
	}
	else
	{
		ant_sent = TRUE;
		G->start->ant = current_ant_index;
		path->ants -= 1;
	}
	room_list = path->room_list;
	push_ants(G, room_list, end_ants);
	if (current_ant_index && current_ant_index <= G->n_ant)
	{
		if (ant_sent)
			current_ant_index += 1;
	}
	else
		current_ant_index = 0;
}

void			travel(t_graph *G)
{
	uint			end_ants;
	t_list_node		*path_list;
	t_path			*path;

	if (DEBUG && !G->debug.nofile)
		ft_putchar('\n');
	G->start->ant = 1;
	end_ants = 0;
	while (end_ants < G->n_ant)
	{
		path_list = G->path_list;
		while (path_list)
		{
			path = (t_path *)path_list->value;
			travel_through_path(G, path, &end_ants);
			path_list = path_list->next;
		}
		ft_putchar('\n');
		G->n_cycle++;
	}
	if (DEBUG && G->debug.cycles)
		ft_printf("Total cycles: "C(YELLOW)"%d\n"C(NO), G->n_cycle);
}

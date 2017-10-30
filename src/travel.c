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

static void		print_ant(t_graph *gr, uint ant_id, t_room *room)
{
	static uint		current_cycle = -1;

	if (DEBUG)
		ft_putstr(C(NO));
	if (current_cycle == gr->n_cycle)
		ft_putchar(' ');
	if (room == gr->end && DEBUG && gr->debug.ants)
	{
		if (ant_id == gr->n_ant)
			ft_putstr(C(PINK));
		else
			ft_putstr(C(GREEN));
	}
	ft_printf("L%d-%s", ant_id, room->name);
	if (DEBUG)
		ft_putstr(C(NO));
	current_cycle = gr->n_cycle;
}

static void		push_ants(t_graph *gr, t_list_node *room_node, uint *end_ants)
{
	t_room		*room;
	t_room		*next_room;

	room = (t_room *)room_node->value;
	if (room == gr->end)
		return ;
	next_room = (t_room *)room_node->next->value;
	push_ants(gr, room_node->next, end_ants);
	if (room->ant)
	{
		if (DEBUG && gr->debug.output)
			print_ant(gr, room->ant, next_room);
		if (next_room == gr->end)
			*end_ants += 1;
	}
	next_room->ant = room->ant;
}

static void		travel_through_path(t_graph *gr, t_path *path, uint *end_ants)
{
	t_list_node		*room_list;
	static uint		current_ant_index = 1;
	t_bool			ant_sent;

	if (!path->ants)
	{
		ant_sent = FALSE;
		gr->start->ant = 0;
	}
	else
	{
		ant_sent = TRUE;
		gr->start->ant = current_ant_index;
		path->ants -= 1;
	}
	room_list = path->room_list;
	push_ants(gr, room_list, end_ants);
	if (current_ant_index && current_ant_index <= gr->n_ant)
	{
		if (ant_sent)
			current_ant_index += 1;
	}
	else
		current_ant_index = 0;
}

void			travel(t_graph *gr)
{
	uint			end_ants;
	t_list_node		*path_list;
	t_path			*path;

	if (DEBUG && !gr->debug.nofile)
		ft_putchar('\n');
	gr->start->ant = 1;
	end_ants = 0;
	while (end_ants < gr->n_ant)
	{
		path_list = gr->path_list;
		while (path_list)
		{
			path = (t_path *)path_list->value;
			travel_through_path(gr, path, &end_ants);
			path_list = path_list->next;
		}
		if (DEBUG && gr->debug.output)
			ft_putchar('\n');
		gr->n_cycle++;
	}
	if (DEBUG && gr->debug.cycles)
		ft_printf("Total cycles: "C(YELLOW)"%d\n"C(NO), gr->n_cycle);
}

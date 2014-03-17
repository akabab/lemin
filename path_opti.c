/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_opti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 17:14:01 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/07 12:37:55 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		complete_path_ants(t_graph *G, uint rest_ants)
{
	t_list_node		*path_list;
	t_path			*path;

	path_list = G->path_list;
	while (path_list && rest_ants)
	{
		path = (t_path *)path_list->value;
		path->ants += 1;
		rest_ants -= 1;
		path_list = path_list->next;
	}
}

void			preset_path_ants(t_graph *G, uint n_cycle)
{
	t_list_node		*path_list;
	t_path			*path;
	uint			total_ants;
	uint			rest_ants;

	total_ants = 0;
	path_list = G->path_list;
	while (path_list)
	{
		path = (t_path *)path_list->value;
		path->ants = n_cycle - path->len;
		total_ants += path->ants;
		path_list = path_list->next;
	}
	rest_ants = G->n_ant - total_ants;
	if (rest_ants)
		complete_path_ants(G, rest_ants);
}

uint			precalc_cycles(t_graph *G)
{
	uint			n_cycle;

	if (!G->n_path)
		return (0);
	n_cycle = (G->n_ant + G->total_paths_len) / G->n_path;
	return (n_cycle);
}

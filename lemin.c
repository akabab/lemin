/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 19:33:59 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/17 12:52:13 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int					resolve(t_graph *gr)
{
	if (DEBUG && !gr->debug.nofile)
		display_entry(gr->entry_list);
	if (find_paths(gr) == 0)
	{
		set_error(ERR_NOPATH);
		print_error(gr, g_err);
		return (-1);
	}
	preset_path_ants(gr, precalc_cycles(gr));
	if (DEBUG)
		display_dbg(gr);
	travel(gr);
	return (0);
}

static t_graph		*graph_init(void)
{
	t_graph		*gr;

	if (!(gr = malloc(sizeof(t_graph))))
		return (NULL);
	gr->n_ant = 0;
	gr->n_room = 0;
	gr->start = NULL;
	gr->end = NULL;
	gr->room_ht = htable_create(1000000);
	gr->room_ht->hash_ft = &hash_djb2;
	gr->n_path = 0;
	gr->total_paths_len = 0;
	gr->path_list = NULL;
	gr->entry_list = NULL;
	gr->n_cycle = 0;
	gr->debug.help = FALSE;
	gr->debug.infos = FALSE;
	gr->debug.rooms = FALSE;
	gr->debug.paths = FALSE;
	gr->debug.ants = FALSE;
	gr->debug.cycles = FALSE;
	gr->debug.nofile = FALSE;
	gr->debug.errors = FALSE;
	return (gr);
}

int					main(int ac, char **av)
{
	t_graph	*gr;

	g_err = ERR_NO;
	if (!(gr = graph_init()))
		return (-1);
	get_args(gr, ac, av);
	if (DEBUG && gr->debug.help)
	{
		display_help();
		free(gr);
		return (0);
	}
	get_entry(gr);
	verif_entry(gr);
	if (g_err > C_ERR)
	{
		print_error(gr, g_err);
		free_memory(gr);
		return (-1);
	}
	resolve(gr);
	free_memory(gr);
	return (0);
}

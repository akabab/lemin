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

int					resolve(t_graph *G)
{
	if (DEBUG && !G->debug.nofile)
		display_entry(G->entry_list);
	if (find_paths(G) == 0)
	{
		set_error(ERR_NOPATH);
		print_error(G, g_err);
		return (-1);
	}
	preset_path_ants(G, precalc_cycles(G));
	if (DEBUG)
		display_dbg(G);
	travel(G);
	return (0);
}

static t_graph		*graph_init(void)
{
	t_graph		*G;

	if (!(G = malloc(sizeof(t_graph))))
		return (NULL);
	G->n_ant = 0;
	G->n_room = 0;
	G->start = NULL;
	G->end = NULL;
	G->room_ht = htable_create(1000000);
	G->room_ht->hash_ft = &hash_djb2;
	G->n_path = 0;
	G->total_paths_len = 0;
	G->path_list = NULL;
	G->entry_list = NULL;
	G->n_cycle = 0;
	G->debug.help = FALSE;
	G->debug.infos = FALSE;
	G->debug.rooms = FALSE;
	G->debug.paths = FALSE;
	G->debug.ants = FALSE;
	G->debug.cycles = FALSE;
	G->debug.nofile = FALSE;
	G->debug.errors = FALSE;
	return (G);
}

int					main(int ac, char **av)
{
	t_graph	*G;

	g_err = ERR_NO;
	if (!(G = graph_init()))
		return (-1);
	get_args(G, ac, av);
	if (DEBUG && G->debug.help)
	{
		display_help();
		free(G);
		return (0);
	}
	get_entry(G);
	verif_entry(G);
	if (g_err > C_ERR)
	{
		print_error(G, g_err);
		free_memory(G);
		return (-1);
	}
	resolve(G);
	free_memory(G);
	return (0);
}

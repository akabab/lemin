/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 10:36:35 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/15 17:39:44 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				display_help(void)
{
	ft_putendl(C(YELLOW)"NAME"C(NO)"\n  lem-in -- flow network simulator\n");
	ft_putendl(C(YELLOW)"USAGE"C(NO)"\n  ./lem-in [-acehinpr] < map\n");
	ft_putendl(C(YELLOW)"OPTIONS"C(NO));
	ft_putendl("  --help	-h	Display help.");
	ft_putendl("  --dbg-infos	-i	Display infos recovered.");
	ft_putendl("  --dbg-rooms	-r	Display rooms with relative adjencies.");
	ft_putendl("  --dbg-paths	-p	Display paths recovered.");
	ft_putendl("  --dbg-ants	-a	Highlights ants when end room is reached.");
	ft_putendl("  --dbg-cycles	-c	Display total cycles.");
	ft_putendl("  --dbg-nofile	-n	Disable file display at start.");
	ft_putendl("  --dbg-errors	-e	Display detailed errors.\n");
	ft_putendl(C(YELLOW)"SUGGESTED"C(NO)"\n  ./lem-in -a -c < map");
}

void				display_dbg(t_graph *G)
{
	if (G->debug.infos)
		display_infos(G);
	if (G->debug.rooms)
		display_rooms(G->room_ht);
	if (G->debug.paths)
		display_paths(G);
}

static void			set_dbg(t_graph *G, char *arg)
{
	if (ft_strequ(arg, "--help") || ft_strequ(arg, "-h"))
		G->debug.help = TRUE;
	else if (ft_strequ(arg, "--dbg-infos") || ft_strequ(arg, "-i"))
		G->debug.infos = TRUE;
	else if (ft_strequ(arg, "--dbg-rooms") || ft_strequ(arg, "-r"))
		G->debug.rooms = TRUE;
	else if (ft_strequ(arg, "--dbg-paths") || ft_strequ(arg, "-p"))
		G->debug.paths = TRUE;
	else if (ft_strequ(arg, "--dbg-ants") || ft_strequ(arg, "-a"))
		G->debug.ants = TRUE;
	else if (ft_strequ(arg, "--dbg-cycles") || ft_strequ(arg, "-c"))
		G->debug.cycles = TRUE;
	else if (ft_strequ(arg, "--dbg-nofile") || ft_strequ(arg, "-n"))
		G->debug.nofile = TRUE;
	else if (ft_strequ(arg, "--dbg-errors") || ft_strequ(arg, "-e"))
		G->debug.errors = TRUE;
}

void				get_args(t_graph *G, int ac, char **av)
{
	int			i;

	if (ac > 1)
	{
		i = 1;
		while (i < ac)
		{
			set_dbg(G, av[i]);
			i++;
		}
	}
}

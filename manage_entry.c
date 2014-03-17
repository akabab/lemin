/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 21:22:31 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/17 13:15:20 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			display_entry(t_list_node *entry_list)
{
	t_list_node		*cursor;
	char			*line;

	if (!entry_list)
		return ;
	cursor = entry_list;
	while (cursor)
	{
		line = (char *)cursor->value;
		ft_putendl(line);
		cursor = cursor->next;
	}
}

void			verif_entry(t_graph *G)
{
	if (G->n_ant < 1)
	{
		set_error(C_ERR_NOENA);
		return ;
	}
	if (G->n_room < 2)
	{
		set_error(C_ERR_NOENR);
		return ;
	}
	if (!G->start)
	{
		set_error(C_ERR_NOSTR);
		return ;
	}
	if (!G->end)
	{
		set_error(C_ERR_NOEDR);
		return ;
	}
}

static void		save_entry(char *line, t_graph *G)
{
	static t_list_node		*last_line = NULL;

	if (!(G->entry_list))
		last_line = list_push_back(&(G->entry_list), line);
	else
		last_line = list_push_back(&last_line, line);
}

static void		get(char *line, t_graph *G)
{
	static char		io = 0;
	static char		status = 1;

	if (line[0] == '#')
		get_comment_or_command(line, G, &io);
	else if (line[0] == '\0')
		set_error(ERR_EMPTL);
	else if (status == 1 && ft_str_isdigit(line))
	{
		get_ant(line, G);
		status = 2;
	}
	else if (ft_strchr(line, '-'))
	{
		get_edge(line, G);
		status = 3;
	}
	else if (status == 2)
		get_room(line, G, &io);
	else
		set_error(ERR_INVDL);
}

void			get_entry(t_graph *G)
{
	char			*line;

	line = NULL;
	while (get_next_line(0, &line) == 1)
	{
		get(line, G);
		line_index++;
		if (g_err)
		{
			free(line);
			if (DEBUG && G->debug.errors)
				print_error(G, g_err);
			return ;
		}
		if (DEBUG && !G->debug.nofile)
			save_entry(line, G);
		else
			free(line);
	}
}

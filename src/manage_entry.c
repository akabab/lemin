/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 21:22:31 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/17 13:21:26 by ycribier         ###   ########.fr       */
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

void			verif_entry(t_graph *gr)
{
	if (gr->n_ant < 1)
	{
		set_error(C_ERR_NOENA);
		return ;
	}
	if (gr->n_room < 2)
	{
		set_error(C_ERR_NOENR);
		return ;
	}
	if (!gr->start)
	{
		set_error(C_ERR_NOSTR);
		return ;
	}
	if (!gr->end)
	{
		set_error(C_ERR_NOEDR);
		return ;
	}
}

static void		save_entry(char *line, t_graph *gr)
{
	static t_list_node		*last_line = NULL;

	if (!(gr->entry_list))
		last_line = list_push_back(&(gr->entry_list), line);
	else
		last_line = list_push_back(&last_line, line);
}

static void		get(char *line, t_graph *gr)
{
	static char		io = 0;
	static char		status = 1;

	if (line[0] == '#')
		get_comment_or_command(line, gr, &io);
	else if (line[0] == '\0')
		set_error(ERR_EMPTL);
	else if (status == 1 && ft_str_isdigit(line))
	{
		get_ant(line, gr);
		status = 2;
	}
	else if (ft_strchr(line, '-'))
	{
		get_edge(line, gr);
		status = 3;
	}
	else if (status == 2)
		get_room(line, gr, &io);
	else
		set_error(ERR_INVDL);
}

void			get_entry(t_graph *gr)
{
	char			*line;

	line = NULL;
	while (get_next_line(0, &line) == 1)
	{
		get(line, gr);
		if (g_err)
		{
			free(line);
			if (DEBUG && gr->debug.errors)
				print_error(gr, g_err);
			return ;
		}
		if (DEBUG && !gr->debug.nofile)
			save_entry(line, gr);
		else
			free(line);
	}
}

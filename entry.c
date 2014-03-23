/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 16:44:48 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/13 12:59:40 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			get_edge(char *line, t_graph *gr)
{
	char		**tab;
	int			len;
	t_room		*room1;
	t_room		*room2;

	tab = ft_strsplit(line , '-');
	len = 0;
	while (tab && tab[len])
		len++;
	if (len != 2)
	{
		set_error(ERR_EDGWF);
		return ;
	}
	if (!(room1 = htable_get(gr->room_ht, tab[0]))
		|| !(room2 = htable_get(gr->room_ht, tab[1])))
	{
		set_error(ERR_EDGRE);
		return ;
	}
	list_push_front(&(room1->adj_list), room2);
	room1->n_adj += 1;
	list_push_front(&(room2->adj_list), room1);
	room2->n_adj += 1;
	free_tab(&tab);
}

static t_room	*get_room_st(char *line, t_graph *gr)
{
	char		**tab;
	int			len;
	t_room		*room;

	tab = ft_strsplit(line, ' ');
	len = 0;
	while (tab && tab[len])
		len++;
	if (len != 3 || tab[0][0] == 'L'
		|| !ft_str_isdigit(tab[1]) || !ft_str_isdigit(tab[2]))
		return (set_error(C_ERR_ROOMWF));
	if (htable_get(gr->room_ht, tab[0]))
		return (set_error(C_ERR_ROOMRE));
	if ((room = malloc(sizeof(t_room))) == NULL)
		return (set_error(C_ERR_NOMEM));
	room->name = ft_strdup(tab[0]);
	room->x = ft_atoi(tab[1]);
	room->y = ft_atoi(tab[2]);
	room->n_adj = 0;
	room->adj_list = NULL;
	room->parent = NULL;
	room->checked = FALSE;
	room->ant = 0;
	free_tab(&tab);
	return (room);
}

void			get_room(char *line, t_graph *gr, char *io)
{
	t_room		*room;

	room = get_room_st(line, gr);
	if (!room)
		return ;
	htable_add(gr->room_ht, room, room->name);
	if (*io == 'i')
		gr->start = room;
	else if (*io == 'o')
		gr->end = room;
	*io = 0;
	gr->n_room++;
}

void			get_comment_or_command(char *line, t_graph *gr, char *io)
{
	if (ft_strequ(&line[1], "#start"))
	{
		if (gr->start)
		{
			set_error(ERR_CCSE);
			return ;
		}
		*io = 'i';
	}
	else if (ft_strequ(&line[1], "#end"))
	{
		if (gr->end)
		{
			set_error(ERR_CCEE);
			return ;
		}
		*io = 'o';
	}
}

void			get_ant(char *line, t_graph *gr)
{
	if (gr->n_ant)
	{
		set_error(C_ERR_ANTAE);
		return ;
	}
	if (ft_strlen(line) > 10 || (ft_strlen(line) == 10 && line[0] > '2')
		|| ft_atoi(line) < 0)
	{
		set_error(C_ERR_ANTIV);
		return ;
	}
	gr->n_ant = ft_atoi(line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 21:56:21 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/23 13:52:12 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdlib.h>
# include "libft.h"
# include "list.h"
# include "lem_htable.h"

typedef unsigned int	uint;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	uint				n_adj;
	t_list_node			*adj_list;
	struct s_room		*parent;
	t_bool				checked;
	uint				ant;
}						t_room;

typedef struct			s_path
{
	uint				id;
	uint				len;
	uint				ants;
	t_list_node			*room_list;
	t_room				*end;
}						t_path;

typedef struct			s_dbg
{
	t_bool				help;
	t_bool				infos;
	t_bool				rooms;
	t_bool				paths;
	t_bool				ants;
	t_bool				cycles;
	t_bool				nofile;
	t_bool				errors;
	t_bool				output;
}						t_dbg;

typedef struct			s_graph
{
	uint				n_ant;
	uint				n_room;
	t_room				*start;
	t_room				*end;
	struct s_htable		*room_ht;
	uint				n_path;
	uint				total_paths_len;
	t_list_node			*path_list;
	t_list_node			*entry_list;
	uint				n_cycle;
	struct s_dbg		debug;
}						t_graph;

/*
**		Options
*/
void	get_args(t_graph *gr, int ac, char **av);
void	display_help(void);

/*
**		Manage entry
*/
void	display_entry(t_list_node *entry_list);
void	verif_entry(t_graph *gr);
void	get_entry(t_graph *gr);

void	get_edge(char *line, t_graph *gr);
void	get_room(char *line, t_graph *gr, char *io);
void	get_comment_or_command(char *line, t_graph *gr, char *io);
void	get_ant(char *line, t_graph *gr);

/*
**		Resolve - Pathfinding
*/
void	bfs(t_graph *gr);
int		find_paths(t_graph *gr);

/*
**		Travel - send ants
*/
void	preset_path_ants(t_graph *gr, uint n_cycle);
uint	precalc_cycles(t_graph *gr);
void	travel(t_graph *gr);

/*
**		FREE
*/
void	free_memory(t_graph *gr);

/*
**		ERROR
*/
typedef enum			e_err
{
	ERR_NO = 0,
	ERR_EDGWF,
	ERR_EDGRE,
	ERR_CCSE,
	ERR_CCEE,
	ERR_EMPTL,
	ERR_INVDL,
	ERR_NOPATH,
	C_ERR,
	C_ERR_ROOMWF,
	C_ERR_ROOMRE,
	C_ERR_NOMEM,
	C_ERR_ANTAE,
	C_ERR_ANTIV,
	C_ERR_NOENA,
	C_ERR_NOENR,
	C_ERR_NOSTR,
	C_ERR_NOEDR
}						t_err;

t_err	g_err;

void	*set_error(int err_id);
void	print_detailed_error(int err_id);
void	print_error(t_graph *gr, int err_id);

/*
**		DEBUG
*/
# define DEBUG		1

# define RED		"31"
# define GREEN		"32"
# define YELLOW		"33"
# define BLUE		"34"
# define PINK		"35"
# define GRBL		"36"
# define GREY		"37"
# define NO			"0"
# define C(X)		"\033[" X "m"
# define CC(X)		"\033[3" X "m"
# define CB(X)		"\x1B[48;1;" X "m"
# define CBNO		"\x1B[0m"

void	display_infos(t_graph *gr);
void	display_rooms(struct s_htable *room_ht);
void	display_paths(t_graph *gr);
void	display_htable(struct s_htable *htable);
void	display_dbg(t_graph *gr);

#endif /* !LEMIN_H */

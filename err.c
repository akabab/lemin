/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 18:44:08 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/14 12:44:05 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	*set_error(int err_id)
{
	static t_bool	err[18] = { FALSE };

	g_err = err_id;
	err[err_id] = TRUE;
	return (NULL);
}

void	print_detailed_error(int err_id)
{
	const char	*err_msg[18] = {
	"none.",
	"edge - wrong format.",
	"edge - one of the rooms doesn't exist.",
	"there is already a starting room.",
	"there is already a ending room.",
	"empty line.",
	"invalid value.",
	"no path found.",
	"[!] critical error.",
	"[!] room - wrong format.",
	"[!] room already exist.",
	"[!] memory allocation failed.",
	"[!] ants recovered already.",
	"[!] ants - invalid value.",
	"[!] not enough ants.",
	"[!] not enough rooms.",
	"[!] no starting room.",
	"[!] no ending room." };

	ft_printf(C(RED)"ERROR(%d): "C(NO)"%s\n", err_id, err_msg[err_id]);
}

void	print_error(t_graph *G, int err_id)
{
	if (DEBUG && G->debug.errors)
		print_detailed_error(g_err);
	else if (err_id > C_ERR)
		ft_putendl("ERROR");
}

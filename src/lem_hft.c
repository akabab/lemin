/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_hft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 11:10:44 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/03 21:38:30 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_htable.h"

/*
**	djb2
**	This algorithm was first reported by Dan Bernstein
**	many years ago in comp.lang.c
*/

unsigned int	hash_djb2(t_htable *htable, char *str)
{
	unsigned int	hash;

	hash = 5381;
	while (str && *str)
	{
		hash = ((hash << 5) + hash) + *str;
		str++;
	}
	return (hash % htable->size);
}

unsigned int	hash_sum(t_htable *htable, char *str)
{
	unsigned int	hash;

	hash = 0;
	while (str && *str)
	{
		hash = *str + (hash << 5) - hash;
		str++;
	}
	return (hash % htable->size);
}

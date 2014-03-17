/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 13:26:45 by ycribier          #+#    #+#             */
/*   Updated: 2013/12/17 13:31:41 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

/*
 *	Return the size of n assuming it's a string and considering '-'
 */

size_t	ft_nbrlen(int n)
{
	int	size;

	size = 0;
	if (n < 0)
		size++;
	while (n / 10 != 0)
	{
		n = n / 10;
		size++;
	}
	size++;
	return (size);
}

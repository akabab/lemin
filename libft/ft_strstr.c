/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 11:05:18 by ycribier          #+#    #+#             */
/*   Updated: 2013/11/25 17:59:06 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(char const *str, char const *to_find)
{
	size_t	len;

	if (*to_find != '\0')
	{
		len = ft_strlen(to_find);
		while (ft_strncmp(str, to_find, len) != 0)
		{
			if (*str == '\0')
				return (NULL);
			str++;
		}
	}
	return ((char *) str);
}

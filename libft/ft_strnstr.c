/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:13:12 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 10:30:21 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)big;
	if (little[j] == '\0')
	{
		return (str);
	}
	while (str[i] != '\0' && i < len)
	{
		while (str[i + j] != '\0' && str[i + j] == little[j] && i + j < len)
			j++;
		if (little[j] == '\0')
			return (str + i);
		i++;
		j = 0;
	}
	return (0);
}

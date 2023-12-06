/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:34:46 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 10:30:27 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		len = 0;
	if (start < 4294967295)
	{
		if (ft_strlen(s + start) < len)
			len = ft_strlen(s + start);
		sub = (char *)malloc((len + 1) * sizeof(char));
		if (!sub)
			return (0);
		ft_strlcpy(sub, s + start, len + 1);
	}
	else
	{
		sub = (char *)malloc((1) * sizeof(char));
		if (!sub)
			return (0);
		sub[0] = '\0';
	}
	return (sub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:10 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 11:50:49 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (len - 1 > i && ft_strchr(set, s1[len - 1]))
		len--;
	if (i > len - 1 || !set)
		return (ft_strdup(""));
	dest = (char *)malloc(len - i + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1 + i, len - i + 1);
	return (dest);
}

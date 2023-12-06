/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:07:11 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 15:54:43 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (is_space(str[i]) == 1)
			i++;
		if (str[i] != '\0')
			count++;
		while (is_space(str[i]) == 0 && str[i] != '\0')
			i++;
	}
	return (count);
}

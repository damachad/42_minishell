/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:22:04 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 10:29:09 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*into_array(int size, int sign, int n)
{
	char	*numb;
	int		str_size;

	if (sign < 0)
		str_size = size + 2;
	else
		str_size = size + 1;
	numb = (char *)malloc(str_size);
	if (numb == 0)
		return (0);
	numb[str_size - 1] = '\0';
	while (str_size > 1)
	{
		numb[str_size - 2] = (n % 10) + 48;
		n = n / 10;
		str_size--;
	}
	if (sign == -1)
		numb[0] = '-';
	return (numb);
}

char	*ft_itoa(int n)
{
	char	*numb;
	int		sign;
	int		n_digits;

	sign = 1;
	if (n == -2147483648)
	{
		numb = ft_strdup("-2147483648");
		return (numb);
	}
	else if (n < 0)
	{
		n *= -1;
		sign *= -1;
	}
	n_digits = count(n);
	numb = into_array(n_digits, sign, n);
	return (numb);
}

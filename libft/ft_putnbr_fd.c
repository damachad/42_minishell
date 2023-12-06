/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:18:29 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 10:29:44 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_dig(int n, int fd)
{
	char	e;

	e = n + '0';
	write(fd, &e, 1);
}

static void	into_array(int n_digit, int n, int fd)
{
	int	digits[10];
	int	count;
	int	i;

	i = 0;
	count = n_digit;
	while (n_digit > 0)
	{
		digits[n_digit - 1] = n % 10;
		n = n / 10;
		n_digit--;
	}
	while (i < count)
	{
		write_dig(digits[i], fd);
		i++;
	}
}

static void	inv(int *ptr, int fd)
{
	*ptr *= -1;
	write(fd, "-", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	np;
	int	count;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
		inv(&n, fd);
	np = n;
	if (np < 10)
	{
		write_dig(np, fd);
		return ;
	}
	count = 0;
	while (np > 0)
	{
		np = np / 10;
		count++;
	}
	into_array(count, n, fd);
}

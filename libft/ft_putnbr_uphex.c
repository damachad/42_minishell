/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uphex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:06:14 by damachad          #+#    #+#             */
/*   Updated: 2023/06/19 14:31:34 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_uphex(unsigned int n)
{
	char	nbr_hex[50];
	char	*ptr;
	int		size;

	size = 0;
	ptr = &nbr_hex[49];
	*ptr = '\0';
	if (n == 0)
	{
		ft_putchar_2('0');
		size++;
	}
	while (n > 0)
	{
		*--ptr = "0123456789ABCDEF"[n % 16];
		n /= 16;
		size++;
	}
	ft_putstr_2(ptr);
	return (size);
}

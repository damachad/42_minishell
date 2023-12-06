/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:06:14 by damachad          #+#    #+#             */
/*   Updated: 2023/06/19 14:32:22 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_add(unsigned long int n)
{
	char	nbr_hex[50];
	char	*ptr;
	int		size;

	size = 0;
	if (n == 0)
	{
		size = ft_putstr_2("(nil)");
		return (size);
	}
	ptr = &nbr_hex[49];
	*ptr = '\0';
	size = ft_putstr_2("0x");
	while (n > 0)
	{
		*--ptr = "0123456789abcdef"[n % 16];
		n /= 16;
		size++;
	}
	ft_putstr_2(ptr);
	return (size);
}

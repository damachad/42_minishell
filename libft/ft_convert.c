/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:01:56 by damachad          #+#    #+#             */
/*   Updated: 2023/06/19 14:32:04 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert(char format, va_list args)
{
	int	size;

	size = 0;
	if (format == 'i' || format == 'd')
		size = ft_putnbr_rec(va_arg(args, int));
	if (format == 'c')
		size = ft_putchar_2((char)va_arg(args, int));
	if (format == 's')
		size = ft_putstr_2(va_arg(args, char *));
	if (format == '%')
		size = ft_putchar_2('%');
	if (format == 'p')
		size = ft_put_add((unsigned long int)va_arg(args, void *));
	if (format == 'u')
		size = ft_putnbr_unsig(va_arg(args, unsigned int));
	if (format == 'x')
		size = ft_putnbr_hex(va_arg(args, unsigned int));
	if (format == 'X')
		size = ft_putnbr_uphex(va_arg(args, unsigned int));
	return (size);
}

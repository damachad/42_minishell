/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:33:41 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 10:29:34 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		chars;

	chars = 0;
	va_start(args, str);
	while (*str != '\0')
	{
		while (*str != '%')
		{
			if (*str == '\0')
			{
				va_end(args);
				return (chars);
			}
			ft_putchar_2(*str);
			chars++;
			str++;
		}
		str++;
		chars += ft_convert(*str, args);
		str++;
	}
	va_end(args);
	return (chars);
}

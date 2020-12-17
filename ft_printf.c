/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbraum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:40:01 by kbraum            #+#    #+#             */
/*   Updated: 2020/12/17 21:25:50 by kbraum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
int		ft_printf(const char *format, ...)
{
	int		n;
	size_t	i;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	n = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c')
				n += ft_putchar_fd(va_arg(ap, int), 1);
			else if (format[i] == 's')
				n += ft_putstr_fd(va_arg(ap, char*), 1);
			else if (format[i] == 'p')
				n += ft_putstr_fd("0x", 1) +
					ft_putfmt_fd((unsigned long)va_arg(ap, void*), 1, 'x');
			else if	(ft_strchr("di", format[i]))
				n += ft_putnbr_fd(va_arg(ap, int), 1);
			else if	(ft_strchr("uxX", format[i]))
				n += ft_putfmt_fd(va_arg(ap, unsigned int), 1, format[i]);
			else if (format[i] == '%' || format[i] == '\0')
				n += ft_putchar_fd('%', 1);
		}
		else
			n += ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(ap);
	return (n);
}

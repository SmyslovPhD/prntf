/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbraum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:40:01 by kbraum            #+#    #+#             */
/*   Updated: 2020/12/18 21:32:23 by kbraum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_conv(va_list ap, const char *format)
{
	int		n;

	n = 0;
	if (*format == 'c')
		n += ft_putchar_fd(va_arg(ap, int), 1);
	else if (*format == 's')
		n += ft_putstr_fd(va_arg(ap, char*), 1);
	else if (*format == 'p')
		n += ft_putstr_fd("0x", 1) +
		ft_putfmt_fd((unsigned long)va_arg(ap, void*), 1, 'x');
	else if (ft_strchr("di", *format))
		n += ft_putnbr_fd(va_arg(ap, int), 1);
	else if (ft_strchr("uxX", *format))
		n += ft_putfmt_fd(va_arg(ap, unsigned int), 1, *format);
	else if (*format == '%' || *format == '\0')
		n += ft_putchar_fd('%', 1);
	return (n);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		n;

	va_start(ap, format);
	n = 0;
	while (*format)
	{
		if (*format == '%')
			ft_printf_conv(ap, ++format);
		else
			n += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (n);
}

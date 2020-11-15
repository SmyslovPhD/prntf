/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbraum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:40:01 by kbraum            #+#    #+#             */
/*   Updated: 2020/12/16 21:21:24 by kbraum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf(const restrict char *format, ...)
{
	int		n;
	size_t	i;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			/*TODO int vmesto void dlya vseh put'ov*/
			if (format[i] == 'c')
				n += ft_putchr_fd(va_arg(ap, char), 1);
			else if (format[i] == 's')
				n += ft_putstr_fd(va_arg(ap, char*), 1);
			else if (format[i] == 'p')
				n += ft_putfmt_fd((long)va_arg(ap, void*), 1, 'x');
			else if	(ft_strchr("di", format[i]))
				n += ft_putnbr_fd(va_arg(ap, int), 1);
			else if	(ft_strchr("uxX", format[i]))
				/*TODO SOZDAT FUNCTION ft_putfmt_fd*/
				n += ft_putfmt_fd(va_arg(ap, unsigned int), 1, fotmat[i]);
			else if (format[i] == '%' || format[i] == '\0')
				n += ft_putchr_fd('%', 1);
		}
		else
			n += ft_putchar(format[i]);
		i++;
	}
}

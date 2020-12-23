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

static char	*ft_printf_str(va_list ap, char c)
{
	char	*s;
	char	*tmp;

	if (c == 'c')
		s = ft_ctos(va_arg(ap, int));
	else if (c == 's')
		s = ft_strdup(va_arg(ap, char*));
	else if (c == 'p')
	{
		tmp = ft_lutof((unsigned long)va_arg(ap, void*), 'x');
		s = ft_strjoin("0x", tmp);
		free(tmp);
	}
	else if (c == 'd' || c == 'i')
		s = ft_itoa(va_arg(ap, int));
	else if (ft_strchr("uxX", c))
		s = ft_lutof(va_arg(ap, unsigned int), c);
	else if (c == '%' || c == '\0')
		s = ft_strdup("%");
	return (s);
}

static int	ft_printf_conv(va_list ap, const char *format)
{
	int		n;
	int		width;
	char	*s;

	n = 0;
	width = ft_atoi(format);
	while (ft_isdigit(*format) || *format == '-')
			format++;
	s = ft_printf_str(ap, *format);
	if (s == 0)
		return (-1);
	if (width >= 0)
	{
		while ((width-- - (int)ft_strlen(s)) > 0)
			n += ft_putchar_fd(' ', 1);
		n += ft_putstr_fd(s, 1);
	}
	else
	{
		n += ft_putstr_fd(s, 1);
		while ((width++ + (int)ft_strlen(s)) < 0)
			n += ft_putchar_fd(' ', 1);
	}
	free(s);
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
		{
			ft_printf_conv(ap, ++format);
			while (ft_isdigit(*format) || *format == '-' || *format == '.')
				format++;
		}
		else
			n += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (n);
}

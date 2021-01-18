/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbraum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:40:01 by kbraum            #+#    #+#             */
/*   Updated: 2021/01/18 21:54:24 by kbraum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char *ft_printf_conv_param(const char *format, int *width, int *prec,
			va_list ap)
{
	*width = *format == '*' ? va_arg(ap, int) : ft_atoi(format);
	while (ft_isdigit(*format) || ft_strchr("+-*", *format))
		format++;
	if (*format == '.')
	{
		format++;
		*prec = *format == '*' ? va_arg(ap, int) : ft_atoi(format);
	}
	else
		*prec = -1;
	while (ft_isdigit(*format) || ft_strchr("+-*", *format))
		format++;
	return ((char*)format);
}

static char	*ft_printf_conv_str(va_list ap, char c)
{
	char	*s;
	char	*tmp;

	s = 0;
	if (c == 'c' || c == '%')
		s = ft_ctos(c == 'c' ? va_arg(ap, int) : '%');
	if (c == 's')
		s = ft_strdup(va_arg(ap, char*));
	if (c == 'p')
	{
		tmp = ft_lutof((unsigned long)va_arg(ap, void*), 'x');
		s = ft_strjoin("0x", tmp);
		free(tmp);
	}
	if (c == 'd' || c == 'i')
		s = ft_itoa(va_arg(ap, int));
	if (ft_strchr("uxX", c))
		s = ft_lutof(va_arg(ap, unsigned int), c);
	if (s == 0)
		s = ft_strdup("(null)");
	return (s);
}

static char	*ft_printf_conv_prec(char *s, const char c, int prec, int *len)
{
	char	*tmp;

	if (prec < 0)
		return (s);
	if (ft_strchr("diuxX%", c))
		while (prec > *len || (ft_strrchr(s, '-') && prec == *len))
		{
			tmp = s;
			s = ft_strjoin("0", tmp);
			(*len)++;
			free(tmp);
		}
	if (ft_strchr("di", c) && (tmp = ft_strrchr(s, '-')))
		ft_cswap(s, tmp);
	if (c == 's' && prec < *len)
		*len = prec;
	return (s);
}

static int	ft_printf_conv(va_list ap, const char *format)
{
	int		n;
	int		width;
	int		prec;
	int		len;
	char	*s;

	n = 0;
	format = ft_printf_conv_param(format, &width, &prec, ap);
	while (ft_isdigit(*format) || ft_strchr(".*+-", *format))
		if (*(format++) == '*')
			va_arg(ap, int);
	s = 0;
	s = ft_printf_conv_str(ap, *format);
	len = *format == 'c' ? 1 : ft_strlen(s);
	s = ft_printf_conv_prec(s, *format, prec, &len);
	while (width > 0 && (width-- - len > 0))
		n += ft_putchar_fd(' ', 1);
	n += write(1, s, len);
	while (width < 0 && (width++ + len) < 0)
		n += ft_putchar_fd(' ', 1);
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
		if (*format == '%' && *(++format) != '\0')
		{
			n += ft_printf_conv(ap, format);
			while (ft_isdigit(*format) || ft_strchr(".*+-", *format))
				if (*(format++) == '*')
					va_arg(ap, int);
		}
		else
			n += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (n);
}

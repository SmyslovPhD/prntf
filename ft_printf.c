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

#include "ft_printf.h"

static char *ft_printf_conv_param(const char *format, int *width, int *prec,
			va_list ap)
{
	*width = *format == '*' ? va_arg(ap, int) : ft_atoi(format);
	while (ft_isdigit(*format) || ft_strchr("+-*", *format))
		format++;
	format += *format == '.';
	*prec = *format == '*' ? va_arg(ap, int) : ft_atoi(format);
	if (*prec == 0 && *format != '*' && ft_atoi(format) == 0)
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

static char	*ft_printf_conv_prec(char *s, const char c, int prec)
{
	char	*tmp;

	if (prec < 0)
		return (s);
	if (ft_strchr("diuxX", c))
		while (prec > (int)ft_strlen(s))
		{
			tmp = s;
			s = ft_strjoin("0", tmp);
			free(tmp);
		}
	if (c == 's' && prec < (int)ft_strlen(s))
		s[prec] = '\0';
	return (s);
}

static int	ft_printf_conv(va_list ap, const char *format)
{
	int		n;
	int		width;
	int		prec;
	char	*s;

	n = 0;
	format = ft_printf_conv_param(format, &width, &prec, ap);
	while (ft_isdigit(*format) || ft_strchr(".*-", *format))
		if (*(format++) == '*')
			va_arg(ap, int);	
	s = 0;
	s = ft_printf_conv_str(ap, *format);
	s = ft_printf_conv_prec(s, *format, prec);
	while (width > 0 && (width-- - (int)ft_strlen(s)) > 0)
		n += ft_putchar_fd(' ', 1);
	n += write(1, s, ft_strlen(s));			
	while (width < 0 && (width++ + (int)ft_strlen(s)) < 0)
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

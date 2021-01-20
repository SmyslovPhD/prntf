/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbraum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:40:01 by kbraum            #+#    #+#             */
/*   Updated: 2021/01/20 20:35:46 by kbraum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*ft_printf_conv_param(const char *f, t_ftprintf_data *param,
				va_list ap)
{
	param->nul_flag = *f == '0';
	param->width = *f == '*' ? va_arg(ap, int) : ft_atoi(f);
	if (*f != '0')
		while (ft_isdigit(*f) || ft_strchr("+-*", *f))
			f++;
	else
		while (*f == '0')
			f++;
	if (*f == '.')
		param->prec = *++f == '*' ? va_arg(ap, int) : ft_atoi(f);
	while (ft_isdigit(*f) || ft_strchr("+-*", *f))
		f++;
	return (f);
}

static char			*ft_printf_conv_str(va_list ap, char c)
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

static char			*ft_printf_conv_prec(char *s, const char c,
				t_ftprintf_data *param)
{
	char	*tmp;

	if (param->prec < 0)
		return (s);
	if (ft_strchr("diuxX%", c))
	{
		if (param->prec == 0 && *s == '0')
			param->len = ft_strlcpy(s, " ", 2);
		param->prec -= param->nul_flag && *s == '-';
		while (param->prec > param->len ||
			(ft_strrchr(s, '-') && param->prec == param->len))
		{
			tmp = s;
			s = ft_strjoin("0", tmp);
			param->len++;
			free(tmp);
		}
	}
	if (ft_strchr("di", c) && (tmp = ft_strrchr(s, '-')))
		ft_cswap(s, tmp);
	if (c == 's' && param->prec < param->len)
		param->len = param->prec;
	return (s);
}

static int			ft_printf_conv(va_list ap, const char *format)
{
	int				n;
	char			*s;
	t_ftprintf_data	param;

	n = 0;
	format = ft_printf_conv_param(format, &param, ap);
	s = ft_printf_conv_str(ap, *format);
	param.len = *format == 'c' ? 1 : ft_strlen(s);
	s = ft_printf_conv_prec(s, *format, &param);
	param.len -= ft_strchr("diuxX%", *format) &&
		param.width == 0 && param.prec == 0;
	while (param.width > 0 && (param.width-- - param.len > 0))
		n += ft_putchar_fd(' ', 1);
	n += write(1, s, param.len);
	while (param.width < 0 && (param.width++ + param.len) < 0)
		n += ft_putchar_fd(' ', 1);
	free(s);
	return (n);
}

int					ft_printf(const char *format, ...)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbraum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:40:01 by kbraum            #+#    #+#             */
/*   Updated: 2021/01/22 18:39:35 by kbraum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
static const char	*ft_printf_conv_param(const char *f, t_ftprintf_data *p,
			va_list ap)
{
	p->flag = *f == '0' ? FLAG_N : 0;
	while (*f == '0')
		f++;
	p->flag = *f == '-' ? FLAG_M : p->flag;
	while (*f == '-')
		f++;
	p->width = *f == '*' ? va_arg(ap, int) : ft_atoi(f);
	p->width = p->flag & FLAG_M ? -ft_abs(p->width) : p->width;
	while (ft_isdigit(*f) || *f == '*')
		f++;
	p->flag = *f == '.' ? (p->flag && !FLAG_N) | FLAG_D : p->flag;
	f += *f == '.';
	if (p->flag & FLAG_D)
		p->prec = *f == '*' ? va_arg(ap, int) : ft_atoi(f);
	else if (p->flag & FLAG_N && p->width)
		p->prec = p->width;
	else
		p->prec = -1;
	while (ft_isdigit(*f) || *f == '*')
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
	if (ft_strchr("ouxX", c))
		s = ft_lutof(va_arg(ap, unsigned int), c);
	if (ft_strchr("sp", c) && s == 0)
		s = ft_strdup("(null)");
	return (s);
}

static char			*ft_printf_conv_prec(char *s, const char c,
				t_ftprintf_data *p)
{
	char	*tmp;

	if (p->prec < 0)
		return (s);
	if (c == 's' && p->flag & FLAG_D && p->prec < p->len)
		p->len = p->prec;
	if (ft_strchr("diouxXp%", c) || (c == 's' && p->flag & FLAG_N))
	{
		if (c != 's' && p->prec == 0)
			p->len = c != 'p' ? ft_strlcpy(s, " ", 2) - 1 : 2;
		p->prec += *s == '-' && !(p->flag & FLAG_N);
		p->prec += (c == 'p') * 2;
		while (p->prec > p->len)
		{
			tmp = s;
			s = ft_strjoin("0", s);
			free(tmp);
			p->len++;
		}
		if ((tmp = ft_strchr(s, c == 'p' ? 'x' : '-')))
			ft_cswap(s + (c == 'p'), tmp);
	}
	return (s);
}

static int			ft_printf_conv(va_list ap, const char *f)
{
	int				n;
	char			*s;
	t_ftprintf_data	p;

	n = 0;
	f = ft_printf_conv_param(f, &p, ap);
	s = ft_printf_conv_str(ap, *f);
	p.len = *f == 'c' ? 1 : ft_strlen(s);
	s = ft_printf_conv_prec(s, *f, &p);
	while (p.width > 0 && (p.width-- - p.len > 0))
		n += ft_putchar_fd(' ', 1);
	n += write(1, s, p.len);
	while (p.width < 0 && (p.width++ + p.len) < 0)
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

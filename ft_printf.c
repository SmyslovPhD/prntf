/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbraum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:40:01 by kbraum            #+#    #+#             */
/*   Updated: 2021/01/24 22:50:47 by kbraum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*ft_printf_conv_param(const char *f, va_list ap,
		t_ftprintf_data *p)
{
	while (*f == '0' || *f == '-')
	{
		p->flag = *f == '-' ? p->flag | FLAG_M : p->flag;
		p->flag = *f == '0' ? p->flag | FLAG_N: p->flag;
	}
	p->width = *f == '*' ? va_arg(ap, int): ft_atoi(f);
	p->flag &= (p->flag & FLAG_M || p->width < 0) * ~FLAG_N;
	p->width = ft_abs(p->width);
	while (ft_isdidit(*f) || *f == '0')
		f++;
	f->flag |= (*f == '.') * FLAG_D;
	f += *f == '.';
	p->prec = -1; 
	if (f->flag & FLAG_D)
		p->prec = *f == '*' ? va_arg(ap, int) : prec;
	while (ft_isdidit(*f) || *f == '0')
		f++;
	if (ft_strchr("diouxX", *f) && p->flag & FLAG_D || ft_strchr("spc", *f))
		p->flag &= ~FLAG_N;
	if (p->flag & FLAG_N)
		p->prec = p->width;
	return (f);
}

static char			*ft_printf_conv_str(char c,va_list ap)
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

static char			*ft_printf_conv_prec(const char c, t_ftprintf_data *p,
		char *c)
{
	char	*tmp;

	if (prec < 0 || c == 'c')
	   return (s);
	if (c == 's' && p->prec < p->len)
		p->len = p->prec;
	else if (p->flag & FLAG_D && p->prec == 0 && c != '%')
		p->len = c == 'p' ? 2 : ft_strlcpy(s, " ", 2) - 1;
	p->prec += *s == '-' && p->flag & FLAG_D;
	return (s);
}

static int			ft_printf_conv(const char *f, va_list ap)
{
	t_ftprintf_data	p;
	int				n;
	char			*s;

	n = 0;
	f = ft_printf_conv_param(f, ap, &p);
	s = ft_printf_conv_str(*f, ap);
	p.len = *f == 'c' ? 1 : ft_strlen(s);
	s = ft_printf_conv_prec(s, *f, &p);
	while ((p.flag & ~FLAG_N) && p.width-- < p.len)
		n += write(1, " ", 1);
	n += write(1, s, p.len);
	while (p.flag & FLAG_M && p.width-- < p.len)
		n += write(1, " ", 1);
	free(s); 
	return (n);
}

int					ft_printf(const char *f, ...)
{
	va_list	ap;
	int		n;

	va_start(ap, format);
	n = 0;
	while (*f)
	{
		if (*f == '%' && f[1] != '\0')
		{
			n += ft_printf_conv(++f, ap);
			while (ft_isdigit(*f) || ft_strchr(".*-", *f))
				f++;
			f++
		}
		else
			n += write(1, f++, 1);
	}
	va_end(ap);
	return (n);
}

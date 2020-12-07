/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbraum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:59:46 by kbraum            #+#    #+#             */
/*   Updated: 2020/11/09 18:46:07 by kbraum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_pow(long n, size_t power)
{
	if (power == 0)
		return (1);
	return (n * ft_pow(n, power - 1));
}

char		*ft_itoa(int n)
{
	size_t	i;
	int		sign;
	char	*p;

	i = 1;
	sign = n < 0 ? -1 : 1;
	while (n / ft_pow(10, i) != 0)
		i++;
	i += n < 0;
	p = (char*)malloc(i + 1);
	if (p == 0)
		return (p);
	p[i--] = 0;
	while (i > 0)
	{
		p[i--] = n % 10 * sign + '0';
		n /= 10;
	}
	p[0] = sign < 0 ? '-' : n % 10 * sign + '0';
	return (p);
}

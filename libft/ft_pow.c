/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbraum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 18:40:24 by kbraum            #+#    #+#             */
/*   Updated: 2020/12/18 20:58:01 by kbraum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int n, size_t i)
{
	if (i == 0)
		return (1);
	return (n * ft_pow(n, --i));
}

unsigned long	ft_powlu(unsigned long n, size_t i)
{
	if (i == 0)
		return (1);
	return (n * ft_powlu(n, --i));
}

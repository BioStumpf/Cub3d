/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:17:57 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/03 09:46:19 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

long	ft_atol(const char *nptr)
{
	int		sign;
	long	res;
	long	digit;

	sign = 1;
	res = 0;
	while (ft_iswhitespace(*nptr))
		nptr++;
	if ((*nptr == '-') || (*nptr == '+'))
		sign = 44 - *nptr++;
	while (ft_isdigit(*nptr))
	{
		digit = *nptr++ - '0';
		if (res < (LONG_MIN + digit) / 10)
			return (errno = ERANGE, LONG_MIN);
		res = res * 10 - digit;
	}
	if (sign > 0)
	{
		if (res == LONG_MIN)
			return (errno = ERANGE, LONG_MIN);
		return (-res);
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_buff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:15:38 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:34:08 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

static size_t	int_len(int n)
{
	size_t	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	abs_digit(int x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

static void	fill_string(char *out, size_t pos, int n)
{
	out[pos--] = 0;
	if (n == 0)
		out[pos] = '0';
	if (n < 0)
		out[0] = '-';
	while (n)
	{
		out[pos] = abs_digit(n % 10) + '0';
		n /= 10;
		pos--;
	}
}

char	*ft_itoa_buff(int n, char *buff, size_t size)
{
	size_t	len;

	if (size < 2)
		return (NULL);
	len = int_len(n);
	if (len >= size)
		len = size - 1;
	fill_string(buff, len, n);
	return (buff);
}

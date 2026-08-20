/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_strings_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:22:31 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/13 10:48:17 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(const char c)
{
	return (write(gfd(), &c, 1));
}

int	ft_putstr(const char *str)
{
	int	i;

	if (!str)
		return (write(gfd(), "(null)", 6));
	i = 0;
	while (str[i])
		i++;
	return (write(gfd(), str, i));
}

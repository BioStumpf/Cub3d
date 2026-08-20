/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:23:29 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 14:36:11 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static bool	add_printed(int printed_bytes, int *tot_bytes)
{
	if (printed_bytes == -1)
	{
		*tot_bytes = -1;
		return (false);
	}
	*tot_bytes += printed_bytes;
	return (true);
}

static int	*get_fd(void)
{
	static int	fd;

	return (&fd);
}

static void	init_fd(int val)
{
	*get_fd() = val;
}

int	gfd(void)
{
	return (*get_fd());
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list		args;
	const char	*cursor;
	int			tot_bytes;
	int			printed_bytes;

	if (!str)
		return (-1);
	init_fd(fd);
	va_start(args, str);
	tot_bytes = 0;
	while (*str)
	{
		cursor = find_option(str);
		printed_bytes = write(gfd(), str, cursor - str);
		if (!add_printed(printed_bytes, &tot_bytes) || !*cursor)
			break ;
		printed_bytes = print_arg(args, cursor + 1);
		if (!add_printed(printed_bytes, &tot_bytes))
			break ;
		str = cursor + 2;
	}
	va_end(args);
	return (tot_bytes);
}
//comment

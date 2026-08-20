/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:46:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/08 09:15:36 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*out;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	out = malloc(len);
	if (!out)
		return (0);
	ft_strlcpy(out, s, len);
	return (out);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:58:52 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/21 15:00:42 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "data.h"

// void	pixel_to_img(t_imge *img, int x, int y, uint64_t color)
// {
// 	char	*pixel_addr;
// 	int		i;
//
// 	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
// 		return ;
// 	pixel_addr = img->addr + (y * img->len + x * img->bytes);
// 	i = -1;
// 	while (++i < img->bytes)
// 		pixel_addr[i] = (color >> (8 * i)) & 0xFF;
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:52:35 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/06 21:00:04 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>


static void			write_base(size_t nbr, size_t base)
{
	size_t			i;

	i = 1;
	if (base == 16)
		write(1, "0x", 2);
	while (nbr / i >= base)
		i *= base;
	while (i)
	{
		write(1, &HEX[nbr / i % base], 1);
		i /= base;
	}
}

void				show_alloc_mem()
{
	size_t			total;
	t_map			*map;
	t_blk			*blk;

	total = 0;
	map = g_map;
	while (map)
	{
		write(1, &TYPES[6 * map->type], 5);
		write(1, " : ", 3);
		if (map->type == LARGE)
		{
			write_base((size_t)((void*)map), 16);
			write(1, "\n", 1);
			write_base((size_t)((void*)map + HEADER_S), 16);
			write(1, " - ", 3);
			write_base((size_t)((void*)map + HEADER_S + map->data_size), 16);
			write(1, " : ", 3);
			write_base(map->data_size, 10);
			total += map->data_size;
			write(1, " bytes\n", 7);
		}
		else
		{
			blk = (void*)map + HEADER_S;
			write_base((size_t)map->data, 16);
			write(1, "\n", 1);
			while (blk->next)
			{
				if (!blk->free)
				{
					write_base((size_t)get_blk_data(map, blk), 16);
					write(1, " - ", 3);
					write_base((size_t)(get_blk_data(map, blk) + blk->size), 16);
					write(1, " : ", 3);
					write_base(blk->size, 10);
					total += blk->size;
					write(1, " bytes\n", 7);
				}
				blk = blk->next;
			}
		}
		map = map->next;
	}
	write(1, "Total : ", 8);
	write_base(total, 10);
	write(1, " bytes\n", 7);
}

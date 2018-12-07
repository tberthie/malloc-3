/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:45:03 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/07 13:56:59 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*allocate_block(t_map *map, size_t size)
{
	t_blk			*blk;

	if ((blk = find_blk(map, size)))
	{
		split_blk(map, blk, size);
		blk->free = 0;
		return (get_blk_data(map, blk));
	}
	return (NULL);
}

static void			*allocate_large(size_t size)
{
	t_map			*map;

	if ((map = create_map_large(size)))
		return ((void*)map + HEADER_S);
	return (NULL);
}

void				*allocate(char type, size_t size)
{
	t_map			*map;
	void			*ptr;

	map = g_map;
	if (type == LARGE)
		return (allocate_large(size));
	while (map)
	{
		if (map->type == type && (ptr = allocate_block(map, size)))
			return (ptr);
		map = map->next;
	}
	if ((map = create_map(type)))
		return (allocate_block(map, size));
	return (NULL);
}

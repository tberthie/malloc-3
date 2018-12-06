/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:45:03 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/06 21:00:38 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*allocate_large(size_t size)
{
	t_map			*map;

	if ((map = create_map_large(size)))
		return ((void*)map + HEADER_S);
	return (NULL);
}

static t_blk		*find_blk(t_map *map, size_t size)
{
	t_blk			*blk;

	blk = (void*)map + HEADER_S;
	while (blk->next)
	{
		if (blk->free && blk->size >= size)
			return (blk);
		blk = blk->next;
	}
	return (NULL);
}

static void			split_blk(t_map *map, t_blk *blk, size_t req_size)
{
	size_t			size;
	t_blk			*next;

	size = blk->size / 2;
	while (size >= req_size && size >= get_type_min(map->type))
	{
		next = (void*)blk + size * ALIGN_T(map->type) / get_type_size(map->type);
		next->free = 1;
		next->next = blk->next;
		blk->next = next;
		next->prev = blk;
		blk->size = size;
		next->size = size;
		size = blk->size / 2;
	}
}


void				*get_blk_data(t_map *map, t_blk *blk)
{
	void			*data;

	data = map->data + (((void*)blk - (void*)map - HEADER_S) * get_type_size(map->type)) / ALIGN_T(map->type);
	return (data);
}

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

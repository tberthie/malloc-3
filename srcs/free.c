/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 15:12:02 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/06 21:03:47 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			delete_map(t_map *map)
{
	t_map		*prev;

	if (map == g_map)
		g_map = map->next;
	else
	{
		prev = g_map;
		while (prev->next != map)
			prev = prev->next;
		prev->next = map->next;
	}
	munmap(map->data, map->data_size);
	munmap(map, map->size);
}

static void				check_free(t_map *map)
{
	t_blk				*blk;

	blk = (void*)map + HEADER_S;
	while (blk)
	{
		if (!blk->free)
			return ;
		blk = blk->next;
	}
	delete_map(map);
}

static void				merge_blk(t_map *map, t_blk *blk)
{
	t_blk				*prev;
	t_blk				*next;

	prev = blk->prev && blk->prev->free ? blk->prev : 0;
	next = blk->next && blk->next->free ? blk->next : 0;
	if (blk->size >= get_type_size(map->type))
		return ;
	if (prev && next && prev->size == blk->size / 2 && next->size == blk->size / 2)
	{
		prev->size = blk->size * 2;
		prev->next = next->next;
	}
	else if (prev && prev->size == blk->size)
		merge_blk(map, prev);
	else if (next && next->size == blk->size)
	{
		if (next->next)
			next->next->prev = blk;
		blk->next = next->next;
		blk->size *= 2;
		merge_blk(map, blk);
	}
}

void					free_allocation(t_map *map, void *ptr)
{
	t_blk				*blk;
	void				*data;

	blk = (void*)map + HEADER_S;
	data = map->data;
	while (blk)
	{
		if (data == ptr)
		{
			blk->free = 1;
			merge_blk(map, blk);
			check_free(map);
			return;
		}
		data = data + blk->size;
		blk = blk->next;
	}
}

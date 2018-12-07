/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:41:31 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/07 14:41:02 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_blk			*find_blk(t_map *map, size_t size)
{
	t_blk		*blk;

	blk = (void*)map + HEADER_S;
	while (blk->next)
	{
		if (blk->free && blk->size >= size)
			return (blk);
		blk = blk->next;
	}
	return (NULL);
}

void			split_blk(t_map *map, t_blk *blk, size_t req_size)
{
	size_t		size;
	t_blk		*next;

	size = blk->size / 2;
	while (size >= req_size && size >= get_type_min(map->type))
	{
		next = (void*)blk + size * ALIGN_T(map->type) /
			get_type_size(map->type);
		next->free = 1;
		next->next = blk->next;
		blk->next = next;
		next->prev = blk;
		blk->size = size;
		next->size = size;
		size = blk->size / 2;
	}
}

void			*get_blk_data(t_map *map, t_blk *blk)
{
	void		*data;

	data = map->data + (((void*)blk - (void*)map - HEADER_S) *
			get_type_size(map->type)) / ALIGN_T(map->type);
	return (data);
}

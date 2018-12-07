/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 14:10:37 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/07 14:24:55 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_blk	*find_map_blk(t_map *map, void *ptr)
{
	t_blk		*blk;
	void		*data;

	blk = (void*)map + HEADER_S;
	data = map->data;
	while (blk->next && data != ptr)
	{
		data = data + blk->size;
		blk = blk->next;
	}
	if (data == ptr)
		return (blk);
	return (0);
}

static void		ft_memcpy(void *dst, void *src, size_t len)
{
	while (len--)
		*(char*)dst++ = *(char*)src++;
}

void			*realloc_large(t_map *map, void *ptr, size_t size)
{
	void		*new;

	if (get_size_type(size) == LARGE && map->size - HEADER_S >= size)
	{
		map->data_size = size;
		return (ptr);
	}
	else if ((new = malloc(size)))
	{
		ft_memcpy(new, ptr, map->data_size > size ? size : map->data_size);
		delete_map(map);
		return (new);
	}
	return (NULL);
}

void			*realloc_block(t_map *map, void *ptr, size_t size)
{
	t_blk		*blk;
	void		*new;

	if ((blk = find_map_blk(map, ptr)))
	{
		if (blk->size >= size && map->type == get_size_type(size))
			return (ptr);
		else if ((new = malloc(size)))
		{
			ft_memcpy(new, ptr, blk->size > size ? size : blk->size);
			free(ptr);
			return (new);
		}
	}
	return (NULL);
}

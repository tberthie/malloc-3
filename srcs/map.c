/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:36:41 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/07 14:21:01 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_map				*find_map(void *ptr)
{
	t_map			*map;

	map = g_map;
	while (map)
	{
		if ((map->data <= ptr && map->data + map->data_size > ptr) ||
			ptr == (void*)map + HEADER_S)
			return (map);
		map = map->next;
	}
	return (0);
}

static void			insert_map(t_map *map)
{
	t_map			*prev;

	if (!g_map)
		g_map = map;
	else if (g_map > map)
	{
		map->next = g_map;
		g_map = map;
	}
	else
	{
		prev = g_map;
		while (prev < map && prev->next)
			prev = prev->next;
		map->next = prev->next;
		prev->next = map;
	}
}

static void			init_control(t_map *map)
{
	size_t			align;
	t_blk			*blk;
	t_blk			*prev;
	size_t			slots;

	slots = SLOTS;
	prev = 0;
	align = get_type_size(map->type);
	blk = (void*)map + HEADER_S;
	while (slots--)
	{
		blk->free = 1;
		blk->size = align;
		blk->next = 0;
		blk->prev = prev;
		if (prev)
			prev->next = blk;
		prev = blk;
		blk = (void*)blk + ALIGN_T(map->type);
	}
}

t_map				*create_map_large(size_t size)
{
	t_map			*map;
	size_t			map_size;

	map_size = ALIGN_P(HEADER_S + size);
	if ((map = mmap(0, map_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED,
			-1, 0)) == MAP_FAILED)
		return (NULL);
	map->type = LARGE;
	map->size = map_size;
	map->data_size = size;
	map->next = 0;
	insert_map(map);
	return (map);
}

t_map				*create_map(char type)
{
	size_t			data_size;
	void			*data_map;
	size_t			control_size;
	t_map			*control_map;

	data_size = ALIGN_P(get_type_size(type) * SLOTS);
	control_size = ALIGN_P(HEADER_S + (get_type_size(type) / get_type_min(type)
				* BLK_S) * SLOTS);
	if ((data_map = mmap(0, data_size, PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_SHARED, -1, 0)) == MAP_FAILED ||
		(control_map = (t_map*)mmap(0, control_size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	control_map->type = type;
	control_map->size = control_size;
	control_map->data = data_map;
	control_map->data_size = data_size;
	control_map->next = 0;
	init_control(control_map);
	insert_map(control_map);
	return (control_map);
}

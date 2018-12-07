/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:15:09 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/07 14:24:50 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_map			*g_map = 0;

void			free(void *ptr)
{
	t_map		*map;

	map = g_map;
	if ((map = find_map(ptr)))
	{
		if (map->type == LARGE && ptr == (void*)map + HEADER_S)
			delete_map(map);
		else if (map->type != LARGE && map->data <= ptr &&
				map->data + map->data_size > ptr)
			free_allocation(map, ptr);
	}
}

void			*malloc(size_t size)
{
	char		type;

	if (size_valid(size))
	{
		size = ALIGN(size);
		type = get_size_type(size);
		return (allocate(type, size));
	}
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	t_map		*map;
	char		type;

	if (size_valid(size))
	{
		size = ALIGN(size);
		type = get_size_type(size);
		if ((map = find_map(ptr)))
		{
			if (map->type == LARGE)
				return (realloc_large(map, ptr, size));
			else
				return (realloc_block(map, ptr, size));
		}
	}
	return (NULL);
}

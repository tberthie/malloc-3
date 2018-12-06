/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:15:09 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/06 21:03:54 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_map			*g_map = 0;

void			free(void *ptr)
{
	t_map		*map;

	map = g_map;
	while (map)
	{
		if (map->type == LARGE && ptr == (void*)map + HEADER_S)
			delete_map(map);
		else if (map->data <= ptr && map->data + map->data_size > ptr)
			free_allocation(map, ptr);
		else
		{
			map = map->next;
			continue ;
		}
		return ;
	}
}

void			*malloc(size_t size)
{
	char		type;

	if (size)
	{
		size = ALIGN(size);
		type = get_size_type(size);
		return (allocate(type, size));
	}
	return (NULL);
}

//void			*realloc(void *ptr, size_t size)
//{
//}

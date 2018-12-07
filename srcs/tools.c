/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:02:45 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/07 13:49:43 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char				size_valid(size_t size)
{
	struct rlimit	limit;

	if (getrlimit(RLIMIT_AS, &limit) == -1)
		return (0);
	return (!(!size || size > limit.rlim_cur));
}

char				get_size_type(size_t size)
{
	if (size > SMALL_S)
		return (LARGE);
	return (size > TINY_S ? SMALL : TINY);
}

size_t				get_type_size(char type)
{
	return (type == SMALL ? SMALL_S : TINY_S);
}

size_t				get_type_min(char type)
{
	return (type == SMALL ? SMALL_M : TINY_M);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:01:14 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/06 20:56:44 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char			get_size_type(size_t size)
{
	if (size > SMALL_S)
		return (LARGE);
	return (size > TINY_S ? SMALL : TINY);
}

size_t			get_type_size(char type)
{
	return (type == SMALL ? SMALL_S : TINY_S);
}

size_t			get_type_min(char type)
{
	return (type == SMALL ? SMALL_M : TINY_M);
}

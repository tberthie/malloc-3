/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:58:26 by tberthie          #+#    #+#             */
/*   Updated: 2018/12/07 14:22:31 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>

# define HEX		"0123456789ABCDEF"
# define TYPES		"TINY\0\0SMALL\0LARGE\0"

enum				e_types {
	TINY, SMALL, LARGE
};

# define ALIGN(x)	((x + 7) & ~7)

# define PAGE_S		getpagesize()
# define ALIGN_P(x)	(x + (PAGE_S - x % PAGE_S))

# define ALIGN_T(t)	(get_type_size(t) / get_type_min(t) * BLK_S)

# define TINY_S		128
# define TINY_M		8

# define SMALL_S	4096
# define SMALL_M	256

# define SLOTS		100

typedef struct		s_blk {

	size_t			free : 1;
	size_t			size : 63;

	struct s_blk	*prev;
	struct s_blk	*next;

}					t_blk;

typedef struct		s_map {

	size_t			type : 2;
	size_t			size : 62;

	void			*data;
	size_t			data_size;

	struct s_map	*next;

}					t_map;

# define HEADER_S	ALIGN(sizeof(t_map))
# define BLK_S		ALIGN(sizeof(t_blk))

extern t_map		*g_map;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);

void				*allocate(char type, size_t size);

void				*get_blk_data(t_map *map, t_blk *blk);
t_blk				*find_blk(t_map *map, size_t size);
void				split_blk(t_map *map, t_blk *blk, size_t req_size);

t_map				*create_map(char type);
t_map				*create_map_large(size_t size);
t_map				*find_map(void *ptr);

void				free_allocation(t_map *map, void *ptr);
void				delete_map(t_map *map);

void				*realloc_large(t_map *map, void *ptr, size_t size);
void				*realloc_block(t_map *map, void *ptr, size_t size);

char				get_size_type(size_t size);
size_t				get_type_size(char type);
size_t				get_type_min(char type);
char				size_valid(size_t size);

void				show_alloc_mem(void);

#endif

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

	struct			s_blk	*prev;
	struct			s_blk	*next;

}					t_blk;

typedef struct		s_map {

	char			type;
	size_t			size;

	void			*data;
	size_t			data_size;

	struct s_map	*next;

}					t_map;

# define HEADER_S	ALIGN(sizeof(t_map))
# define BLK_S		ALIGN(sizeof(t_blk))

extern t_map		*g_map;

void				*malloc(size_t size);
void				free(void *ptr);

void				*allocate(char type, size_t size);
void				*get_blk_data(t_map *map, t_blk *blk);

t_map				*create_map(char type);
t_map				*create_map_large(size_t size);

void				free_allocation(t_map *map, void *ptr);
void				delete_map(t_map *map);

char				get_size_type(size_t size);
size_t				get_type_size(char type);
size_t				get_type_min(char type);

//char				size_valid(size_t size);

void				show_alloc_mem();

#endif

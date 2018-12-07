# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 22:18:00 by tberthie          #+#    #+#              #
#    Updated: 2018/12/07 19:03:14 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

OBJS = $(addsuffix .o, $(addprefix objs/, \
			functions tools allocate map output free blocks realloc ))

NAME = libft_malloc_$(HOSTTYPE).so
LNK = libft_malloc.so

all: objs $(NAME)

objs:
	mkdir objs

$(NAME): $(OBJS)
	gcc -o $(NAME) $(OBJS) -shared
	ln -fs $(NAME) $(LNK)

objs/%.o: srcs/%.c
	gcc -o $@ -c $< -I includes -Wall -Wextra

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)
	rm -f $(LNK)

re: fclean all

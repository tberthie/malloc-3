# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 22:18:00 by tberthie          #+#    #+#              #
#    Updated: 2018/12/06 15:29:48 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

OBJS = $(addsuffix .o, $(addprefix objs/, \
			functions type tools allocate map output free ))

NAME = libft_malloc_$(HOSTTYPE).so
LNK = libft_malloc.so

all: objs $(NAME)

objs:
	mkdir objs

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ln -fs $(NAME) $(LNK)

objs/%.o: srcs/%.c
	gcc -o $@ -c $< -I includes -Wall -Wextra -g

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)
	rm -f $(LNK)

re: fclean all
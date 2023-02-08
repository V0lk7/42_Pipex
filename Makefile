# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jduval <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 13:27:39 by jduval            #+#    #+#              #
#    Updated: 2023/02/08 15:15:44 by jduval           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	pipex

MAKEFLAGS	+=	--no-print-directory

SRC_DIR		:=	mandatory

SRCS		:=	main.c	\
				px_parsing_path.c	\
				px_parsing_files.c	\

SRCS		:=	$(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR	:=	.build

OBJS		:=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPS		:=	$(OBJS:.o=.d)

CC			:=	clang

CFLAGS		:=	-Werror -Wall

DIR_DUP		=	mkdir -p $(@D)

all: $(NAME)
.PHONY: all

$(NAME): $(OBJS)
	@${MAKE} -C libft/
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $@
	$(info CREATED $@)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS) 

clean:
	@${MAKE} -C libft/ clean
	rm -rf .build
.PHONY:clean

fclean: clean 
	@${MAKE} -C libft/ fclean
	rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re

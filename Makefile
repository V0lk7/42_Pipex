# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jduval <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 13:27:39 by jduval            #+#    #+#              #
#    Updated: 2023/02/16 18:16:08 by jduval           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	pipex

MAKEFLAGS	+=	--no-print-directory

###############################################################################

LIBS 		=	ft

LIBS_TARGET =	libft/libft.a

INCLUDES	=	libft/include

###############################################################################

BUILD_DIR 	= 	.build_pipex

SRC_DIR		=	mandatory

SRCS 		:=	main.c	\
				px_free.c	px_list_utils.c	\
				px_parsing_files.c	\
				px_parsing_path.c	\
				px_parse_cmd.c	\
				px_init_list.c	\
				px_utils.c	\
				px_single_quote.c	\
				px_parsing.c	\
				px_exec_cmds.c	\

SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJS 		= $(SRCS:%.c=$(BUILD_DIR)/%.o)

DEPS 		= $(OBJS:.o=.d)


###############################################################################

CC 			=	clang

CFLAGS 		= 	-Werror -Wextra -Wall -ggdb3 -O3

CPPFLAGS 	=	-MMD -MP $(addprefix -I,$(INCLUDES))

LDFLAGS		=	$(addprefix -L,$(dir $(LIBS_TARGET)))

LDLIBS		=	$(addprefix -l,$(LIBS))

DIRDUP 		= 	mkdir -p $(@D) 


###############################################################################

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	@$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(dir $@)

$(BUILD_DIR)/%.o : %.c
	@$(DIRDUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS) test.mk

bonus: 
	$(MAKE) BONUS=1 all
.PHONY:bonus

###############################################################################

clean:
	@${MAKE} -C libft/ clean
	rm -rf .build_pipex
.PHONY:clean

fclean: clean 
	@${MAKE} -C libft/ fclean
	rm -f pipex
.PHONY: fclean

re: fclean all
.PHONY: re


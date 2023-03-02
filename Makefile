# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jduval <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 13:27:39 by jduval            #+#    #+#              #
#    Updated: 2023/03/02 09:34:41 by jduval           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifdef BONUS
NAME 		=	pipex_bonus
else
NAME		= 	pipex
endif

MAKEFLAGS	+=	--no-print-directory

###############################################################################

LIBS 		=	ft

LIBS_TARGET =	libft/libft.a

INCLUDES	=	libft/include

###############################################################################

ifdef BONUS
BUILD_DIR 	= 	.build_pipex_bonus
else
BUILD_DIR 	= 	.build_pipex
endif

SRC_DIR			=	mandatory
SRC_DIR_BNS		=	bonus

SRCS 		:=	px_parsing_path.c		\
				px_parse_cmd.c			\
				px_single_quote.c		\
				px_init_list.c			\
				px_parsing.c			\
				px_exec_cmds.c			\
				px_first_exec.c			\
				px_last_exec.c			\
				px_free.c				\
				px_list_utils.c			\
				px_utils.c				\

SRCS_BONUS	:=	pipex_bonus.c				\
				px_parse_hdoc_bonus.c		\
				px_exec_cmds_bonus.c		\

SRCS		:=	$(SRCS:%=$(SRC_DIR)/%)
SRCS_BONUS	:=	$(SRCS_BONUS:%=$(SRC_DIR_BNS)/%)

ifdef BONUS
SRCS += $(SRCS_BONUS)
else
SRCS += mandatory/pipex.c
endif

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
	$(MAKE) -C libft/
	$(MAKE) BONUS=1 all
.PHONY:bonus

###############################################################################

clean:
	@${MAKE} -C libft/ clean
	rm -rf .build_pipex .build_pipex_bonus
.PHONY:clean

fclean: clean
	@${MAKE} -C libft/ fclean
	rm -f pipex pipex_bonus
.PHONY: fclean

re: fclean all
.PHONY: re


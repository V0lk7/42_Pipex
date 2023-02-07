# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jduval <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 13:27:39 by jduval            #+#    #+#              #
#    Updated: 2023/02/07 12:11:06 by jduval           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ifdef BONUS
#NAME 		:=	pipex_bonus
#else
NAME 		=	pipex
#endif

MAKEFLAGS	+=	--no-print-directory

###############################################################################

LIBS 		:=	ft

LIBS_TARGET :=	libft/libft.a	\

INCLUDES	:=	libft/include 	\

###############################################################################

BUILD_DIR 	:= 	.build

SRCS_DIR	:=	mandatory

SRCS 		:=	main.c	\

SRCS 		:=	$(SRCS:%=$(SRCS_DIR)/%)

OBJS 		:=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPS 		:=	$(OBJS:.o=.d)

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
	@$(MAKE) -C $(dir $@)

$(BUILD_DIR)/%.o : %.c
	@$(DIRDUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

#bonus: 
#	$(MAKE) BONUS=1 all
#.PHONY:bonus

###############################################################################

clean:
	@${MAKE} -C libft/ clean
	rm -rf .build
.PHONY:clean

fclean: clean 
	@${MAKE} -C libft/ fclean
	rm -f pipex pipex_bonus
.PHONY: fclean

re: fclean all
.PHONY: re

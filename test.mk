# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jduval <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 10:53:32 by jduval            #+#    #+#              #
#    Updated: 2023/02/14 11:31:13 by jduval           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TEST		:=	$(shell find test -name '*.c')
TEST_OBJS	:=	$(TEST:%.c=$(BUILD_DIR)/%.o)

ARCHIVE		:=	test/pipex.a
RUNNER		:=	test/test

$(ARCHIVE): $(OBJS)
	ar rcs $(ARCHIVE) $(OBJS)

$(TEST_OBJS): CPPFLAGS+= -I test/

$(TEST_OBJS): CFLAGS = -Wall -Wextra -ggdb3

$(RUNNER): $(LIBS_TARGET) $(ARCHIVE) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TEST_OBJS) $(ARCHIVE) $(LDLIBS) -o $(RUNNER)

clear:
	rm -rf $(ARCHIVE)
.PHONY: clear

rclean: 
	rm -rf test/test
.PHONY: rclean

test: clear fclean rclean $(RUNNER)
.PHONY: test

run:	
	cd test/ && ./greatest_parallel ./test
.PHONY: run

v:	
	cd test/ && ./greatest_parallel -v ./test
.PHONY: v

gdb:
	cd test/ && gdb -args ./test
.PHONY: gdb

.PHONY: test

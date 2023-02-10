/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:26:50 by jduval            #+#    #+#             */
/*   Updated: 2023/02/10 16:55:42 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"
#include "../include/pipex.h"

static char	*str;

static void	setup(void *data)
{
	(void) data;
	str = NULL;
}

static void teardown(void *data)
{
	(void) data;
	if (str != NULL)
		free (str);
}

TEST	full_str1(void)
{
	str = ft_only_cmd("cat -e -a -b");
	ASSERT_STR_EQ("cat", str);
	PASS();
}

TEST	full_str2(void)
{
	str = ft_only_cmd("cat");
	ASSERT_STR_EQ("cat", str);
	PASS();
}

TEST	str_empty(void)
{
	str = ft_only_cmd("");
	ASSERT_STR_EQ("", str);
	PASS();
}

TEST	str_null(void)
{
	str = ft_only_cmd(NULL);
	if (str == NULL)
		ASSERT_EQ(1, 1);
	else
		ASSERT_EQ(1, 0);
	PASS();
}

SUITE (only_cmd)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(full_str1);
	RUN_TEST(full_str2);
	RUN_TEST(str_empty);
	RUN_TEST(str_null);
}

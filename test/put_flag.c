/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:14:04 by jduval            #+#    #+#             */
/*   Updated: 2023/02/14 11:26:59 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"
#include "../include/pipex.h"

static char *str;

static void	setup(void *data)
{
	(void) data;
	str = NULL;
}

static void	teardown(void *data)
{
	(void) data;
	free (str);
}

TEST	test_one(void)
{
	str = ft_strdup("'je suis'");
	ft_put_flag(&str);
	ASSERT_EQ_FMT(-128, str[3], "%d");
	PASS();
}

TEST	test_two(void)
{
	str = ft_strdup(" 'hell yeah'");
	ft_put_flag(&str);
	ASSERT_EQ_FMT(32, str[0], "%d");
	ASSERT_EQ_FMT(-128, str[6], "%d");
	PASS();
}

TEST	test_three(void)
{
	str = ft_strdup("hell ");
	ft_put_flag(&str);
	ASSERT_EQ_FMT(32, str[4], "%d");
	PASS();
}

TEST	test_four(void)
{
	str = ft_strdup("h'ell '");
	ft_put_flag(&str);
	ASSERT_EQ_FMT(-128, str[5], "%d");
	PASS();
}

SUITE (put_flag)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(test_one);
	RUN_TEST(test_two);
	RUN_TEST(test_three);
	RUN_TEST(test_four);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:48:50 by jduval            #+#    #+#             */
/*   Updated: 2023/02/14 10:14:12 by jduval           ###   ########.fr       */
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
	free(str);
}

TEST	test_one(void)
{
	str = ft_strdup("je");
	str = ft_put_space(str);
	ASSERT_STR_EQ("je ", str);
	PASS();
}

TEST	test_two(void)
{
	str = ft_strdup("suis");
	str = ft_put_space(str);
	ASSERT_STR_EQ("suis ", str);
	PASS();
}

TEST	test_three(void)
{
	str = ft_strdup("ton");
	str = ft_put_space(str);
	ASSERT_STR_EQ("ton ", str);
	PASS();
}

TEST	test_four(void)
{
	str = ft_strdup("pere");
	str = ft_put_space(str);
	ASSERT_STR_EQ("pere ", str);
	PASS();
}

SUITE(put_space)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(test_one);
	RUN_TEST(test_two);
	RUN_TEST(test_three);
	RUN_TEST(test_four);
}

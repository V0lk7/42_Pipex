/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:40:46 by jduval            #+#    #+#             */
/*   Updated: 2023/02/13 17:58:03 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"
#include "../include/pipex.h"

TEST	no_quote(void)
{
	ASSERT_EQ_FMT(0, ft_find_quotes("je suis ton pere"), "%d");
	PASS();
}

TEST	one_quote(void)
{
	ASSERT_EQ_FMT(1, ft_find_quotes("je sui's ton pere"), "%d");
	PASS();
}

TEST	two_quote(void)
{
	ASSERT_EQ_FMT(2, ft_find_quotes("je sui's to'n pere"), "%d");
	PASS();
}

TEST	three_quote(void)
{
	ASSERT_EQ_FMT(3, ft_find_quotes("je sui's to'n pere'"), "%d");
	PASS();
}

TEST	four_quote(void)
{
	ASSERT_EQ_FMT(4, ft_find_quotes("'je sui's to'n pere'"), "%d");
	PASS();
}

TEST	full_quote(void)
{
	ASSERT_EQ_FMT(10, ft_find_quotes("''''''''''"), "%d");
	PASS();
}

SUITE (find_quote)
{
	RUN_TEST(no_quote);
	RUN_TEST(one_quote);
	RUN_TEST(two_quote);
	RUN_TEST(three_quote);
	RUN_TEST(four_quote);
	RUN_TEST(full_quote);
}

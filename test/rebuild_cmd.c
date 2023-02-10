/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:56:57 by jduval            #+#    #+#             */
/*   Updated: 2023/02/11 00:09:27 by jduval           ###   ########.fr       */
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

TEST	no_space(void)
{
	str = ft_only_cmd("cat-e-a");
	str = ft_rebuild_cmd("cat-e-a", str);
	ASSERT_STR_EQ("cat-e-a", str);
	PASS();
}

TEST	with_space(void)
{
	str = ft_only_cmd("cat -e -a");
	str = ft_rebuild_cmd("cat -e -a", str);
	ASSERT_STR_EQ("cat -e -a", str);
	PASS();
}

TEST	with_path(void)
{
	str = ft_only_cmd("/usr/bin/cat -e -a");
	str = ft_rebuild_cmd("/usr/bin/cat -e -a", str);
	ASSERT_STR_EQ("/usr/bin/cat -e -a", str);
	PASS();
}

SUITE (rebuild_cmd)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(no_space);
	RUN_TEST(with_space);
	RUN_TEST(with_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:07:33 by jduval            #+#    #+#             */
/*   Updated: 2023/02/14 10:37:51 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"
#include "../include/pipex.h"

static char *str;

static char **cmd0;
static char **cmd1;
static char **cmd2;

static void ft_free_all(char **tab0, char **tab1, char **tab2)
{
	int	i;

	i = 0;
	while (tab0[i])
	{
		free (tab0[i]);
		i++;
	}
	free (tab0);
	i = 0;
	while (tab1[i])
	{
		free (tab1[i]);
		i++;
	}
	free (tab1);
	i = 0;
	while (tab2[i])
	{
		free (tab2[i]);
		i++;
	}
	free (tab2);
}

static void	setup(void *data)
{
	(void) data;
	str = NULL;
	cmd0 = ft_split("/usr/bin/cat", ' ');
	cmd1 = ft_split("/usr/bin/cat -e", ' ');
	cmd2 = ft_split("/usr/bin/cat -e -a -d", ' ');
}

static void	teardown(void *data)
{
	(void) data;
	free (str);
	ft_free_all(cmd0, cmd1, cmd2);
}

TEST	zero_args(void)
{
	str = ft_rebuild_str(cmd0);
	ASSERT_STR_EQ("/usr/bin/cat ", str);
	PASS();
}

TEST	one_args(void)
{
	str = ft_rebuild_str(cmd1);
	ASSERT_STR_EQ("/usr/bin/cat -e ", str);
	PASS();
}

TEST	three_args(void)
{
	str = ft_rebuild_str(cmd2);
	ASSERT_STR_EQ("/usr/bin/cat -e -a -d ", str);
	PASS();
}

SUITE (rebuild_str)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(zero_args);
	RUN_TEST(one_args);
	RUN_TEST(three_args);
}

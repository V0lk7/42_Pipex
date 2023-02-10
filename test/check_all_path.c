/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:11:33 by jduval            #+#    #+#             */
/*   Updated: 2023/02/11 00:14:39 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"
#include "../include/pipex.h"

static char	*str;
static char	**tab;
static char *envp[] = {"/nfs/homes/jduval/.local/bin/",
						"/nfs/homes/jduval/bin/",
						"/usr/local/sbin/",
						"/usr/local/bin/",
						"/usr/sbin/",
						"/usr/bin/",
						"/bin/",
						"/usr/games/",
						"/usr/local/games/",
						"/snap/bin/",	
						NULL};

static void	setup(void *data)
{
	(void) data;
	str = NULL;
	tab = NULL;
}

static void teardown(void *data)
{
	(void) data;
	if (str != NULL)
		free (str);
	if (tab != NULL)
	{
		int i = 0;
		while (tab[i])
			free(tab[i++]);
		free(tab);	
	}
}

TEST	valid_command_no_option(void)
{
	str = ft_only_cmd("cat");
	tab = ft_check_all_path("cat", str, envp);
	ASSERT_STR_EQ("/usr/bin/cat", tab[0]);
	if (tab[1] != NULL)
		ASSERT_EQ(0, 1);
	else
		ASSERT_EQ(0, 0);
	PASS();
}

TEST	valid_command_option(void)
{
	str = ft_only_cmd("cat -e");
	tab = ft_check_all_path("cat -e", str, envp);
	ASSERT_STR_EQ("/usr/bin/cat", tab[0]);
	ASSERT_STR_EQ("-e", tab[1]);
	if (tab[2] != NULL)
		ASSERT_EQ(0, 1);
	else
		ASSERT_EQ(0, 0);
	PASS();
}

TEST	invalid_command(void)
{
	str = ft_only_cmd("catzz -e");
	tab = ft_check_all_path("catzz -e", str, envp);
	ASSERT_STR_EQ("catzz", tab[0]);
	ASSERT_STR_EQ("-e", tab[1]);
	if (tab[2] != NULL)
		ASSERT_EQ(0, 1);
	else
		ASSERT_EQ(0, 0);
	PASS();
}

SUITE (check_all_path)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(valid_command_no_option);
	RUN_TEST(valid_command_option);
	RUN_TEST(invalid_command);
}

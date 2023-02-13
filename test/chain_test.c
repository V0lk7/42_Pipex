/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:52:09 by jduval            #+#    #+#             */
/*   Updated: 2023/02/13 15:41:31 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "greatest.h"

static t_cmd	*chain;

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
	chain = NULL;
}

static void teardown(void *data)
{
	(void) data;
	ft_free_all_cmd(&chain);
}

static int	count_nodes(t_cmd *head)
{
	t_cmd	*tmp;
	int		i = 0;

	tmp = head;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

TEST	infile_ok_2_nodes(void)
{
	char	*tab[] = {"./pipex", "infile", "ls -la", "cat -e", "outfile", NULL};
	int		argc = 5;
	t_file	file = INFILE;
	chain = ft_create_chain(argc, file, tab, envp);
	ASSERT_EQ_FMT(2, count_nodes(chain), "%d");
	ASSERT_STR_EQ("/usr/bin/ls", chain->cmd[0]);
	ASSERT_STR_EQ("-la", chain->cmd[1]);
	ASSERT_STR_EQ("/usr/bin/cat", chain->next->cmd[0]);
	ASSERT_STR_EQ("-e", chain->next->cmd[1]);
	PASS();
}	

TEST	infile_ok_3_nodes(void)
{
	char	*tab[] = {"./pipex", "infile", "ls -la", "cat -e", "grep 'hello world'", "outfile", NULL};
	int		argc = 6;
	t_file	file = INFILE;
	chain = ft_create_chain(argc, file, tab, envp);
	ASSERT_EQ_FMT(3, count_nodes(chain), "%d");
	ASSERT_STR_EQ("/usr/bin/ls", chain->cmd[0]);
	ASSERT_STR_EQ("-la", chain->cmd[1]);
	ASSERT_STR_EQ("/usr/bin/cat", chain->next->cmd[0]);
	ASSERT_STR_EQ("-e", chain->next->cmd[1]);
	ASSERT_STR_EQ("/usr/bin/grep", chain->next->next->cmd[0]);
	ASSERT_STR_EQ("'hello world'", chain->next->next->cmd[1]);
	PASS();
}

SUITE (chain_test)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(infile_ok_2_nodes);
	RUN_TEST(infile_ok_3_nodes);
}

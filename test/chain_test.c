/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:52:09 by jduval            #+#    #+#             */
/*   Updated: 2023/02/14 16:48:49 by jduval           ###   ########.fr       */
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

TEST	infile_0(void)
{
	char	*tab[] = {"./pipex", "infile", "ls -la", "cat -e", "outfile", NULL};
	int		argc = 5;
	t_file	file = INFILE;
	chain = ft_create_chain(argc, file, tab, envp);
	ASSERT_EQ_FMT(2, count_nodes(chain), "%d");
	ASSERT_EQ_FMT(INFILE, chain->flag, "%d");
	ASSERT_EQ_FMT(INFILE, chain->next->flag, "%d");
	ASSERT_STR_EQ("/usr/bin/ls", chain->cmd[0]);
	ASSERT_STR_EQ("-la", chain->cmd[1]);
	ASSERT_STR_EQ("/usr/bin/cat", chain->next->cmd[0]);
	ASSERT_STR_EQ("-e", chain->next->cmd[1]);
	PASS();
}	

TEST	infile_1(void)
{
	char	*tab[] = {"./pipex", "infile", "ls -la", "cat -e", "grep 'hello world'", "outfile", NULL};
	int		argc = 6;
	t_file	file = INFILE;
	chain = ft_create_chain(argc, file, tab, envp);
	ASSERT_EQ_FMT(3, count_nodes(chain), "%d");
	ASSERT_EQ_FMT(INFILE, chain->flag, "%d");
	ASSERT_EQ_FMT(INFILE, chain->next->flag, "%d");
	ASSERT_EQ_FMT(INFILE, chain->next->next->flag, "%d");
	ASSERT_STR_EQ("/usr/bin/ls", chain->cmd[0]);
	ASSERT_STR_EQ("-la", chain->cmd[1]);
	ASSERT_STR_EQ("/usr/bin/cat", chain->next->cmd[0]);
	ASSERT_STR_EQ("-e", chain->next->cmd[1]);
	ASSERT_STR_EQ("/usr/bin/grep", chain->next->next->cmd[0]);
	ASSERT_STR_EQ("'hello world'", chain->next->next->cmd[1]);
	PASS();
}

TEST	infile_2(void)
{
	char	*tab[] = {"./pipex", "infile", "grep 'je suis", "cat -e", "outfile", NULL};
	int		argc = 5;
	t_file	file = INFILE;
	chain = ft_create_chain(argc, file, tab, envp);
	ASSERT_EQ_FMT(2, count_nodes(chain), "%d");
	ASSERT_EQ_FMT(INFILE, chain->flag, "%d");
	ASSERT_EQ_FMT(INFILE, chain->next->flag, "%d");
	ASSERT_STR_EQ("/usr/bin/grep", chain->cmd[0]);
	ASSERT_STR_EQ("'je", chain->cmd[1]);
	ASSERT_STR_EQ("suis", chain->cmd[2]);
	ASSERT_STR_EQ("/usr/bin/cat", chain->next->cmd[0]);
	ASSERT_STR_EQ("-e", chain->next->cmd[1]);
	PASS();
}

TEST	outfile_0(void)
{
	char	*tab[] = {"./pipex", "infile", "ls -la", "cat -e", "outfile", NULL};
	int		argc = 5;
	t_file	file = NO_INFILE;
	chain = ft_create_chain(argc, file, tab, envp);
	ASSERT_EQ_FMT(1, count_nodes(chain), "%d");
	ASSERT_EQ_FMT(NO_INFILE, chain->flag, "%d");
	ASSERT_STR_EQ("/usr/bin/cat", chain->cmd[0]);
	ASSERT_STR_EQ("-e", chain->cmd[1]);
	PASS();
}	

TEST	outfile_1(void)
{
	char	*tab[] = {"./pipex", "infile", "ls -la", "cat -e", "grep 'hello world'", "outfile", NULL};
	int		argc = 6;
	t_file	file = NO_INFILE;
	chain = ft_create_chain(argc, file, tab, envp);
	ASSERT_EQ_FMT(2, count_nodes(chain), "%d");
	ASSERT_EQ_FMT(NO_INFILE, chain->flag, "%d");
	ASSERT_EQ_FMT(NO_INFILE, chain->next->flag, "%d");
	ASSERT_STR_EQ("/usr/bin/cat", chain->cmd[0]);
	ASSERT_STR_EQ("-e", chain->cmd[1]);
	ASSERT_STR_EQ("/usr/bin/grep", chain->next->cmd[0]);
	ASSERT_STR_EQ("'hello world'", chain->next->cmd[1]);
	PASS();
}

TEST	outfile_2(void)
{
	char	*tab[] = {"./pipex", "infile", "grep 'je suis", "cat -e", "outfile", NULL};
	int		argc = 5;
	t_file	file = NO_INFILE;
	chain = ft_create_chain(argc, file, tab, envp);
	ASSERT_EQ_FMT(1, count_nodes(chain), "%d");
	ASSERT_EQ_FMT(NO_INFILE, chain->flag, "%d");
	ASSERT_STR_EQ("/usr/bin/cat", chain->cmd[0]);
	ASSERT_STR_EQ("-e", chain->cmd[1]);
	PASS();
}

SUITE (chain_test)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(infile_0);
	RUN_TEST(infile_1);
	RUN_TEST(infile_2);
	RUN_TEST(outfile_0);
	RUN_TEST(outfile_1);
	RUN_TEST(outfile_2);
}

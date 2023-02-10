/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:00:24 by jduval            #+#    #+#             */
/*   Updated: 2023/02/10 23:58:37 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "greatest.h"

static char	*str;
static char **tab;

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
		int	i = 0;
		while(tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

TEST	find_path(void)
{
	char	*tab1[] = {"hey", "boy", "PATH=je:suis:ton:pere", "general", NULL};
	char	*tab2[] = {"hey", "boy", "eh bah nan", "general", NULL};
	char	*tab3[] = {NULL};
	
	ASSERT_EQ_FMT(2, ft_find_path(tab1), "%d");	
	ASSERT_EQ_FMT(-1, ft_find_path(tab2), "%d");	
	ASSERT_EQ_FMT(-1, ft_find_path(tab3), "%d");	
	PASS();
}

TEST	remake_path(void)
{
	char	*tab1 = "PATH=je:suis:ton:pere";
	char	*str2;

	str2 = ft_remake_path(NULL);
	if (str2 != NULL)
		ASSERT_EQ(0, 1);
	else
		ASSERT_EQ(0, 0);
	str = ft_remake_path(tab1);
	ASSERT_STR_EQ("je:suis:ton:pere", str);
	PASS();
}

TEST	envp_path(void)
{
	char	*tab1[] = {"hey", "boy", "PATH=je:suis", "general", NULL};
	char	*tab2[] = {"je/", "suis/", NULL};
	int		i = 0;
	tab = ft_envp_to_path(tab1);

	while(tab[i] != NULL)
	{
		ASSERT_STR_EQ(tab2[i], tab[i]);
		i++;
	}
	PASS();
}

SUITE (path_test)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(find_path);
	RUN_TEST(remake_path);
	RUN_TEST(envp_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:07:22 by jduval            #+#    #+#             */
/*   Updated: 2023/02/09 17:05:53 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"
#include "../include/pipex.h"

static t_cmd	*ptr;
static t_cmd	*ptr1;
static t_cmd	*ptr2;

static void	setup(void *data)
{
	(void) data;
	ptr = NULL;
	ptr1 = NULL;
	ptr2 = NULL;
}

static void teardown(void *data)
{
	(void) data;
	if (ptr != NULL)
		free(ptr);
	if (ptr1 != NULL)
		free(ptr1);
	if (ptr2 != NULL)
		free(ptr2);
}

t_cmd	*ft_init_link(void)
{
	char	*tab[] = {"hello", NULL};
	char	*tab1[] = {"there", NULL};
	char	*tab2[] = {"general", NULL};
	int		a = 0;
	int		b = 1;
	int		c = 2;
	ptr = ft_new_node(tab, a);
	ptr1 = ft_new_node(tab1, b);
	ptr2 = ft_new_node(tab2, c);
	ptr->next = ptr1;
	ptr1->next = ptr2;
	ptr2->next = NULL;
	return (ptr);
}

TEST	new_node(void)
{
	char	*tab[] = {"hello", NULL};
	int		a = 0;
	
	ptr = ft_new_node(tab, a); 
	ASSERT_STR_EQ("hello", ptr->cmd[0]);
	ASSERT_EQ(0, ptr->error);
	PASS();
}

TEST	last_node(void)
{
	t_cmd	*tmp = ft_init_link();

	tmp = ft_last_node(tmp);
	ASSERT_STR_EQ("general", "general");
	ASSERT_EQ(2, tmp->error);
	PASS();;
}

TEST	add_node_full(void)
{
	char	*tab[] = {"hello", NULL};
	char	*tab2[] = {"there", NULL};
	int		a = 0;
	int		b = 1;
	ptr = ft_new_node(tab, a);
	ptr1 = ft_new_node(tab2, b);

	ft_add_back_node(&ptr, ptr1);
	ASSERT_STR_EQ("there", ptr->next->cmd[0]);
	ASSERT_EQ(1, ptr->next->error);
	PASS();
}

TEST	add_node_empty(void)
{
	char	*tab[] = {"hello", NULL};
	int		a = 0;
	ptr1 = ft_new_node(tab, a);
	t_cmd	*tmp = NULL;

	ft_add_back_node(&tmp, ptr1);
	ASSERT_STR_EQ("hello", tmp->cmd[0]);
	ASSERT_EQ(0, tmp->error);
	PASS();
}

SUITE (list_suit)
{
	SET_SETUP(setup, NULL);
	SET_TEARDOWN(teardown, NULL);
	RUN_TEST(new_node);
	RUN_TEST(last_node);
	RUN_TEST(add_node_full);
	RUN_TEST(add_node_empty);
}

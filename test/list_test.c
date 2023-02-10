/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:07:22 by jduval            #+#    #+#             */
/*   Updated: 2023/02/10 14:57:21 by jduval           ###   ########.fr       */
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
	ptr = ft_new_node(tab);
	ptr1 = ft_new_node(tab1);
	ptr2 = ft_new_node(tab2);
	ptr->next = ptr1;
	ptr1->next = ptr2;
	ptr2->next = NULL;
	return (ptr);
}

TEST	new_node(void)
{
	char	*tab[] = {"hello", NULL};
	
	ptr = ft_new_node(tab); 
	ASSERT_STR_EQ("hello", ptr->cmd[0]);
	PASS();
}

TEST	last_node(void)
{
	t_cmd	*tmp = ft_init_link();

	tmp = ft_last_node(tmp);
	ASSERT_STR_EQ("general", "general");
	PASS();;
}

TEST	add_node_full(void)
{
	char	*tab[] = {"hello", NULL};
	char	*tab2[] = {"there", NULL};
	ptr = ft_new_node(tab);
	ptr1 = ft_new_node(tab2);

	ft_add_back_node(&ptr, ptr1);
	ASSERT_STR_EQ("there", ptr->next->cmd[0]);
	PASS();
}

TEST	add_node_empty(void)
{
	char	*tab[] = {"hello", NULL};
	ptr1 = ft_new_node(tab);
	t_cmd	*tmp = NULL;

	ft_add_back_node(&tmp, ptr1);
	ASSERT_STR_EQ("hello", tmp->cmd[0]);
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

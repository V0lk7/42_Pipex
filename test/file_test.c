/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:02:12 by jduval            #+#    #+#             */
/*   Updated: 2023/02/16 16:02:40 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"
#include "../include/pipex.h"

TEST	infile(void)
{
	char	*test[] = {"lambda", "file.txt", NULL};
	char	*test1[] = {"lambda", "hello", NULL};
	t_file	value = ft_infile(test);
	ASSERT_EQ_FMT(INFILE, value, "%d");
	ASSERT_EQ(NO_INFILE, ft_infile(test1));
	PASS();	
}

SUITE (file_test)
{
	RUN_TEST(infile);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:02:12 by jduval            #+#    #+#             */
/*   Updated: 2023/02/09 17:09:47 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"
#include "../include/pipex.h"

TEST	infile(void)
{
	char	*test[] = {"lambda", "test/file.txt", NULL};
	char	*test1[] = {"lambda", "hello", NULL};
	t_file	value = ft_infile(test);
	ASSERT_EQ_FMT(INFILE, value, "%d");
	ASSERT_EQ(NO_INFILE, ft_infile(test1));
	PASS();	
}

TEST	outfile(void)
{
	char	*test[] = {"lambda", "test/outfile.txt", NULL};
	char	*test1[] = {"lambda", "well.txt", NULL};
	int		fd = 0;

	ASSERT_EQ(TRUE, ft_outfile(2, test));
	ASSERT_EQ(TRUE, ft_outfile(2, test1));
	fd = open("well.txt", O_RDONLY);
	if (fd == -1)
		ASSERT_EQ(-1, 0);
	ASSERT_EQ(1, 1);
	remove("well.txt");
	PASS();
}

SUITE (file_test)
{
	RUN_TEST(infile);
	RUN_TEST(outfile);
}

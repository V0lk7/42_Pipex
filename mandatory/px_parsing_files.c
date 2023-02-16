/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:58:35 by jduval            #+#    #+#             */
/*   Updated: 2023/02/16 16:03:22 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_file	ft_infile(char **argv)
{
	int	fd;
	int	flag;

	flag = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("infile: ");
		return (NO_INFILE);
	}
	flag = close(fd);
	if (flag == -1)
	{
		perror("close infile ");
		return (ERROR);
	}
	return (INFILE);
}

t_file	ft_files(char **argv)
{
	t_file	infile;

	infile = ft_infile(argv);
	if (infile == ERROR)
		exit (0);
	return (infile);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:58:35 by jduval            #+#    #+#             */
/*   Updated: 2023/02/09 16:21:29 by jduval           ###   ########.fr       */
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
		perror(NULL);
		return (NO_INFILE);
	}
	flag = close(fd);
	if (flag == -1)
	{
		perror(NULL);
		return (ERROR);
	}
	return (INFILE);
}

t_bool	ft_outfile(int argc, char **argv)
{
	int	fd;
	int	flag;

	fd = open(argv[argc - 1], O_CREAT | O_TRUNC, S_IRWXU);
	flag = 0;
	if (fd == -1)
		perror(NULL);
	if (fd > -1)
	{
		flag = close(fd);
		if (flag == -1)
		{
			perror(NULL);
			return (FALSE);
		}
	}
	return (TRUE);
}

t_file	ft_files(int argc, char **argv)
{
	t_file	infile;
	t_bool	flag;

	infile = ft_infile(argv);
	if (infile == ERROR)
		exit (0);
	flag = ft_outfile(argc, argv);
	if (flag == FALSE)
		exit(0);
	return (infile);
}

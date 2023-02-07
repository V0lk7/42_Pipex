/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:54:48 by jduval            #+#    #+#             */
/*   Updated: 2023/02/07 16:58:05 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	ft_infile(char **argv)
{
	int	fd;
	int	flag;

	flag = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		return (TRUE);
	}
	flag = close(fd);
	if (flag == -1)
	{
		perror(NULL);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	ft_outfile(int argc, char **argv)
{
	int	fd;
	int	flag;

	fd = open(argv[argc - 1], O_CREATE, S_IRWXU);
	flag = 0;
	if (fd == -1)
	{
		perror(NULL);	
		return (FALSE);
	}
	flag = close(fd);
	if (flag == -1)
	{
		perror(NULL);
		return (FALSE);
	}
	return (TRUE);
}

void	ft_files(int argc, char **argv)
{
	int	flag;

	flag = ft_infile(argv);
	if (flag == FALSE)
		exit (0);
	flag = ft_outfile(argc, argv);
	if (flag == FALSE)
		exit(0);
	return ;
}

t_cmd	ft_parsing(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	**paths;

	ft_files(argc, argv);
	paths = ft_envp_to_paths(envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_change_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:09:45 by jduval            #+#    #+#             */
/*   Updated: 2023/02/21 08:51:14 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_dup_last_cmd(int *pipefd, char *argv, t_cmd *cmd)
{
	int	fd;

	fd = open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		printf("3\n");
		ft_error_function(cmd);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		printf("4\n");
		ft_error_function(cmd);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("5\n");
		ft_error_function(cmd);
	}
	ft_close_fds(fd, pipefd[0], pipefd[1]);
}

void	ft_dup_first_cmd(int *pipefd, char *argv, t_cmd *cmd)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		ft_free_all_cmd(&cmd);
		ft_close_fds(pipefd[0], pipefd[1], -1);
		exit(0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("1\n");
		ft_error_function(cmd);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		printf("2\n");
		ft_error_function(cmd);
	}
	ft_close_fds(fd, pipefd[0], pipefd[1]);
}

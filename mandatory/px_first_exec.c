/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_first_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:20:05 by jduval            #+#    #+#             */
/*   Updated: 2023/02/22 14:12:41 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_quit_first(void)
{
	perror(NULL);
	exit(0);
}

static int	ft_dup_first_cmd(int *pipefd, int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("first cmd dup2 n1 ");
		ft_close_fds(pipefd[0], pipefd[1], fd);
		return (-1);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("first cmd dup2 n2 ");
		ft_close_fds(pipefd[0], pipefd[1], fd);
		return (-1);
	}
	ft_close_fds(fd, pipefd[0], pipefd[1]);
	return (0);
}

static void	ft_exec_first_cmd(t_cmd *cmd, int fd, int *pipefd, char **envp)
{
	if (cmd->valid == -1)
	{
		ft_error_cmd(cmd->cmd[0]);
		ft_free_lstcmd(&cmd);
		ft_close_fds(fd, pipefd[0], pipefd[1]);
		exit(0);
	}
	if (ft_dup_first_cmd(pipefd, fd) == -1)
	{
		ft_free_lstcmd(&cmd);
		exit(0);
	}
	if (execve(cmd->cmd[0], cmd->cmd, envp) == -1)
	{
		ft_free_lstcmd(&cmd);
		ft_quit_first();
	}
}

int	ft_first_cmd(t_cmd *cmd, char *file, int *pipefd, char **envp)
{
	int		fd;
	pid_t	pid;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		ft_close_fds(pipefd[0], pipefd[1], fd);
		ft_free_lstcmd(&cmd);
		ft_quit_first();
	}
	if (pid == 0)
		ft_exec_first_cmd(cmd, fd, pipefd, envp);
	if (pid > 0)
	{
		if (close(fd) == -1)
		{
			ft_free_lstcmd(&cmd);
			ft_quit_first();
		}
	}
	return (1);
}

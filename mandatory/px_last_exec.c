/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_last_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:55:39 by jduval            #+#    #+#             */
/*   Updated: 2023/02/22 14:10:40 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_quit_last(void)
{
	perror(NULL);
	exit(0);
}

static int	ft_dup_last_cmd(int *pipefd, int fd)
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("last cmd dup2 n1 ");
		ft_close_fds(pipefd[0], pipefd[1], fd);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("last cmd dup2 n2 ");
		ft_close_fds(pipefd[0], pipefd[1], fd);
		return (-1);
	}
	ft_close_fds(fd, pipefd[0], pipefd[1]);
	return (0);
}

static void	ft_exec_last_cmd(t_cmd *cmd, int fd, int *pipefd, char **envp)
{
	if (cmd->valid == -1)
	{
		ft_error_cmd(cmd->cmd[0]);
		ft_free_lstcmd(&cmd);
		ft_close_fds(fd, pipefd[0], pipefd[1]);
		exit(0);
	}
	if (ft_dup_last_cmd(pipefd, fd) == -1)
	{
		ft_free_lstcmd(&cmd);
		exit(0);
	}
	if (execve(cmd->cmd[0], cmd->cmd, envp) == -1)
	{
		ft_free_lstcmd(&cmd);
		ft_quit_last();
	}
}

int	ft_last_cmd(t_cmd *cmd, char *file, int *pipefd, char **envp)
{
	int		fd;
	pid_t	pid;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		ft_close_fds(pipefd[0], pipefd[1], fd);
		ft_free_lstcmd(&cmd);
		ft_quit_last();
	}
	if (pid == 0)
		ft_exec_last_cmd(cmd, fd, pipefd, envp);
	if (pid > 0)
	{
		if (close(fd) == -1)
		{
			ft_free_lstcmd(&cmd);
			ft_quit_last();
		}
	}
	return (1);
}

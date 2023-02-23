/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_mult_first.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:06 by jduval            #+#    #+#             */
/*   Updated: 2023/02/23 16:51:37 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static int	ft_dup_first_cmd(int file_fd, t_pipes *fds)
{
	if (dup2(file_fd, STDIN_FILENO) == -1)
	{
		perror("first multcmd dup2 n1 ");
		ft_close_fds(fds, file_fd);
		return (-1);
	}
	if (dup2(fds->pipe1[1], STDOUT_FILENO) == -1)
	{
		perror("first multcmd dup2 n2 ");
		ft_close_fds(fds, file_fd);
		return (-1);
	}
	ft_close_fds(fds, file_fd);
	return (0);
}

static void	ft_exec_cmd(t_cmd *cmd, int file_fd, t_pipes *fds, char **envp)
{
	if (cmd->valid == -1)
	{
		ft_error_cmd(cmd->cmd[0]);
		ft_free_lstcmd(&cmd);
		ft_close_fds(fds, file_fd);
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

int	ft_first_multcmd(t_cmd *cmd, char *file, t_pipes *fds, char **envp)
{
	int		file_fd;
	pid_t	pid;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		ft_close_fds(fds, file_fd);
		ft_free_lstcmd(&cmd);
		ft_quit_first();
	}
	if (pid == 0)
		ft_exec_cmd(cmd, file_fd, fds, envp);
	if (pid > 0)
	{
		if (close(file_fd) == -1)
		{
			ft_free_lstcmd(&cmd);
			ft_quit_first();
		}
	}
	return (1);
}

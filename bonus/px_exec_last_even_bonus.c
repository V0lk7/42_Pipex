/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_last_even_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:09:10 by jduval            #+#    #+#             */
/*   Updated: 2023/02/24 18:03:41 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static int	ft_dup_last_even(t_pipes *fds, int file_fd)
{
	if (dup2(fds->pipe2[0], STDIN_FILENO) == -1)
	{
		perror("last even multcmd dup2 n1 ");
		ft_close_pfd(fds, file_fd);
		return (-1);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		perror("last even multcmd dup2 n2 ");
		ft_close_pfd(fds, file_fd);
		return (-1);
	}
	close(fds->pipe2[0]);
	close(file_fd);
	return (0);
}

static void	ft_exec_last_even(t_cmd *cmd, int fd, t_pipes *fds, char **envp)
{
	if (cmd->valid == -1 || cmd->valid == 2)
	{
		ft_error_cmd(cmd->cmd[0]);
		ft_free_lstcmd(&cmd);
		ft_close_pfd(fds, fd);
		exit(0);
	}
	if (ft_dup_last_even(fds, fd) == -1)
	{
		ft_free_lstcmd(&cmd);
		exit(0);
	}
	if (execve(cmd->cmd[0], cmd->cmd, envp) == -1)
	{
		ft_free_lstcmd(&cmd);
		ft_error_quit();
	}
}

int	ft_last_even_cmd(t_cmd *cmd, char *file, t_pipes *fds, char **envp)
{
	int		file_fd;
	pid_t	pid;

	if (cmd->valid <= 0)
		file_fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		file_fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file_fd == -1)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		ft_close_pfd(fds, file_fd);
		ft_free_lstcmd(&cmd);
		ft_error_quit();
	}
	if (pid == 0)
		ft_exec_last_even(cmd, file_fd, fds, envp);
	close(file_fd);
	close(fds->pipe1[0]);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_inter_odd_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:49:08 by jduval            #+#    #+#             */
/*   Updated: 2023/02/24 18:02:46 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static int	ft_dup_inter_odd(t_pipes *fds)
{
	if (dup2(fds->pipe2[0], STDIN_FILENO) == -1)
	{
		perror("odd dup2 n1 ");
		ft_close_pfd(fds, -1);
		return (-1);
	}
	if (dup2(fds->pipe1[1], STDOUT_FILENO) == -1)
	{
		perror("odd dup2 n2 ");
		ft_close_pfd(fds, -1);
		return (-1);
	}
	close(fds->pipe2[0]);
	close(fds->pipe1[1]);
	return (0);
}

static void	ft_exec_inter_odd(t_cmd *cmd, t_pipes *fds, char **envp)
{
	if (cmd->valid == -1)
	{
		ft_error_cmd(cmd->cmd[0]);
		ft_free_lstcmd(&cmd);
		ft_close_pfd(fds, -1);
		exit(0);
	}
	if (ft_dup_inter_odd(fds) == -1)
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

int	ft_inter_odd_cmd(t_cmd *cmd, t_pipes *fds, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_close_pfd(fds, -1);
		ft_free_lstcmd(&cmd);
		ft_error_quit();
	}
	if (pid == 0)
		ft_exec_inter_odd(cmd, fds, envp);
	close(fds->pipe2[0]);
	close(fds->pipe1[1]);
	return (1);
}

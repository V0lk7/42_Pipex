/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_inter_even.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:04 by jduval            #+#    #+#             */
/*   Updated: 2023/02/23 17:45:25 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static int	ft_dup_inter_even(t_pipes *fds)
{
	if (dup2(fds->pipe1[0], STDIN_FILENO) == -1)
	{
		perror("even dup2 n1 ");
		ft_close_fds(fds, file_fd);
		return (-1);
	}
	if (dup2(fds->pipe2[1], STDOUT_FILENO) == -1)
	{
		perror("even dup2 n2 ");
		ft_close_fds(fds, -1);
		return (-1);
	}
	ft_close_fds(fds, -1);
	return (0);
}

static void	ft_exec_inter_even(t_cmd *cmd, t_pipes *fds, char **envp)
{
	if (cmd->valid == -1)
	{
		ft_error_cmd(cmd->cmd[0]);
		ft_free_lstcmd(&cmd);
		ft_close_fds(fds, -1);
		exit(0);
	}
	if (ft_dup_inter_even(fds) == -1)
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

int	ft_inter_even_cmd(t_cmd *cmd, t_pipes *fds, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_close_fds(fds, -1);
		ft_free_lstcmd(&cmd);
		ft_quit_first();
	}
	if (pid == 0)
		ft_exec_inter_even(cmd, fds, envp);
	else
		return (1);
}

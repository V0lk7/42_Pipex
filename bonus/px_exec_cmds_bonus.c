/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_cmds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:42:11 by jduval            #+#    #+#             */
/*   Updated: 2023/03/01 17:10:20 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	ft_loop_mlt_cmd(t_cmd *cmd, int argc, char **argv, char **envp)
{
	t_fds	fd;
	int		wstatus;
	pid_t	pid;

	fd.read = open(argv[1], O_RDONLY);
	if (fd.read == -1)
	{
		perror(NULL);
		cmd = ft_free_cmd(&cmd);
	}
	while (cmd != NULL)
	{
		ft_open_fd(cmd, &fd, argv[argc - 1]);
		pid = fork();
		if (pid == 0)
			ft_child(&fd, cmd, envp);
		cmd = ft_free_cmd(&cmd);
		ft_close_fds(fd.write, fd.read, -1);
		fd.read = fd.pipe[0];
	}
	waitpid(pid, &wstatus, 0);
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
	return (WEXITSTATUS(wstatus));
}

void	ft_open_fd(t_cmd *cmd, t_fds *fd, char *str)
{
	if (cmd->next == NULL)
		fd->write = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
	{
		if (pipe(fd->pipe) == -1)
		{
			ft_free_lstcmd(&cmd);
			if (fd->read > -1)
				close (fd->read);	
			ft_error_quit();
		}
		fd->write = fd->pipe[1];
	}
}

void	ft_child(t_fds *fd, t_cmd *cmd, char **envp)
{
	ft_dup_fds(fd, cmd);
	if (cmd->valid == -1)
	{
		ft_error_cmd(cmd->cmd[0]);
		ft_free_lstcmd(&cmd);
		exit(0);
	}
	execve(cmd->cmd[0], cmd->cmd, envp);
	perror(NULL);
	ft_free_lstcmd(&cmd);
	exit(0);
}

void	ft_dup_fds(t_fds *fd, t_cmd *cmd)
{
	if (fd->read < 0)
	{
		ft_close_fds(fd->pipe[0], fd->write, -1);
		ft_free_lstcmd(&cmd);
		exit(0);
	}
	if(dup2(fd->read, STDIN_FILENO) == -1)
	{
		ft_close_fds(fd->read, fd->write, fd->pipe[0]);
		ft_free_lstcmd(&cmd);
		ft_error_quit();
	}
	if(dup2(fd->write, STDOUT_FILENO) == -1)
	{
		ft_close_fds(fd->read, fd->write, fd->pipe[0]);
		ft_free_lstcmd(&cmd);
		ft_error_quit();
	}
	ft_close_fds(fd->read, fd->write, fd->pipe[0]);
}

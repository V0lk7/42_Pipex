/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_cmds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:42:11 by jduval            #+#    #+#             */
/*   Updated: 2023/03/08 13:10:01 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	ft_loop_mlt_cmd(t_cmd *cmd, int argc, char **argv, char **envp)
{
	t_fds	fd;
	pid_t	pid;
	int		wstatus;

	fd.read = ft_open_infile(argv[1], cmd);
	while (cmd != NULL)
	{
		ft_open_fd(cmd, &fd, argv[argc - 1]);
		pid = fork();
		if (pid == 0)
			ft_child(&fd, cmd, envp);
		if (cmd->next != NULL)
			ft_close_fds(fd.write, fd.read, -1);
		fd.read = fd.pipe[0];
		cmd = ft_free_cmd(&cmd);
	}
	waitpid(pid, &wstatus, 0);
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
	ft_close_fds(fd.write, fd.read, -1);
	return (WEXITSTATUS(wstatus));
}

int	ft_open_infile(char *file, t_cmd *cmd)
{
	int	fd;

	if (cmd->valid == 1)
		return (-2);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror(NULL);
	return (fd);
}

void	ft_open_fd(t_cmd *cmd, t_fds *fd, char *str)
{
	if (cmd->next == NULL)
	{
		if (cmd->valid == 1 || cmd->valid == 2)
			fd->write = open(str, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd->write = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd->write == -1)
		{
			ft_free_lstcmd(&cmd);
			ft_error_quit();
		}
		return ;
	}
	if (pipe(fd->pipe) == -1)
	{
		ft_free_lstcmd(&cmd);
		if (fd->read > -1)
			close (fd->read);
		ft_error_quit();
	}
	fd->write = fd->pipe[1];
	if (fd->read == -2)
		ft_fill_pipe(fd, cmd);
}

void	ft_child(t_fds *fd, t_cmd *cmd, char **envp)
{
	if (fd->write == -1 || fd->read == -1)
	{
		ft_close_fds(fd->read, fd->write, fd->pipe[0]);
		ft_free_lstcmd(&cmd);
		exit(0);
	}
	ft_dup_fds(fd, cmd);
	if (cmd->valid == -1)
	{
		ft_error_cmd(cmd->cmd[0]);
		ft_free_lstcmd(&cmd);
		exit(0);
	}
	execve(cmd->cmd[0], cmd->cmd, envp);
	if ((cmd->valid == 0 || cmd->valid == 1) && cmd->position != 1)
		perror(NULL);
	ft_free_lstcmd(&cmd);
	exit(0);
}

void	ft_dup_fds(t_fds *fd, t_cmd *cmd)
{
	if (cmd->valid == 0 || cmd->valid == 1)
	{
		if (fd->read > 2 && dup2(fd->read, STDIN_FILENO) == -1)
		{
			ft_close_fds(fd->read, fd->write, fd->pipe[0]);
			ft_free_lstcmd(&cmd);
			ft_error_quit();
		}
		if (!(cmd->valid == 1 && cmd->position == 1)
			&& dup2(fd->write, STDOUT_FILENO) == -1)
		{
			ft_close_fds(fd->read, fd->write, fd->pipe[0]);
			ft_free_lstcmd(&cmd);
			ft_error_quit();
		}
	}
	ft_close_fds(fd->read, fd->write, fd->pipe[0]);
}

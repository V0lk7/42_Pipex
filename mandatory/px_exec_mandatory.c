/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_mandatory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:42:11 by jduval            #+#    #+#             */
/*   Updated: 2023/03/06 17:25:36 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_open_infile_mandatory(char *file);
static void	ft_open_fd_mandatory(t_cmd *cmd, t_fds *fd, char *str);
static void	ft_child_mandatory(t_fds *fd, t_cmd *cmd, char **envp);
static void	ft_dup_mandatory(t_fds *fd, t_cmd *cmd);

int	ft_exec_mandatory(t_cmd *cmd, int argc, char **argv, char **envp)
{
	t_fds	fd;
	pid_t	pid;
	int		wstatus;

	fd.read = ft_open_infile_mandatory(argv[1]);
	while (cmd != NULL)
	{
		ft_open_fd_mandatory(cmd, &fd, argv[argc - 1]);
		pid = fork();
		if (pid == 0)
			ft_child_mandatory(&fd, cmd, envp);
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

static int	ft_open_infile_mandatory(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror(NULL);
	return (fd);
}

static void	ft_open_fd_mandatory(t_cmd *cmd, t_fds *fd, char *str)
{
	if (cmd->next == NULL)
	{
		fd->write = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd->write == -1)
			perror(NULL);
	}
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

static void	ft_child_mandatory(t_fds *fd, t_cmd *cmd, char **envp)
{
	if (fd->write == -1 || fd->read == -1)
	{
		ft_close_fds(fd->read, fd->write, fd->pipe[0]);
		ft_free_lstcmd(&cmd);
		exit(0);
	}
	ft_dup_mandatory(fd, cmd);
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

static void	ft_dup_mandatory(t_fds *fd, t_cmd *cmd)
{
	if (cmd->valid > -1)
	{
		if (fd->read > 2 && dup2(fd->read, STDIN_FILENO) == -1)
		{
			ft_close_fds(fd->read, fd->write, fd->pipe[0]);
			ft_free_lstcmd(&cmd);
			ft_error_quit();
		}
		if (dup2(fd->write, STDOUT_FILENO) == -1)
		{
			ft_close_fds(fd->read, fd->write, fd->pipe[0]);
			ft_free_lstcmd(&cmd);
			ft_error_quit();
		}
	}
	ft_close_fds(fd->read, fd->write, fd->pipe[0]);
}

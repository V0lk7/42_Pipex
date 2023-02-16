/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:13:57 by jduval            #+#    #+#             */
/*   Updated: 2023/02/16 19:09:58 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_close_files(int fd1, int fd2, int fd3)
{
	int	flag;
	
	flag = 0;
	if (fd1 > 2 && fd2 > 2 && fd3 > 2)
	{
		flag = close(fd1);
		if (flag == -1)
			ft_error_function();
		flag = close(fd2);
		if (flag == -1)
			ft_error_function();
		flag = close(fd3);
		if (flag == -1)
			ft_error_function();
	}
	else
		return ;
}

void	ft_child(t_cmd *cmd, char *argv, int *pipefd, char **envp)
{
	int	fd;

	if (cmd->next == NULL)
	{
		fd = open(argv, O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (fd == -1)
			ft_error_function();
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			ft_error_function();
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_error_function();
		ft_close_files(fd, pipefd[0], pipefd[1]);
		if (execve(cmd->cmd[0], cmd->cmd, envp) == -1)
			ft_error_function();
	}
	fd = open(argv, O_RDWR);
	if (fd == -1)
		ft_error_function();
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error_function();
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_error_function();
	ft_close_files(fd, pipefd[0], pipefd[1]);
	if (execve(cmd->cmd[0], cmd->cmd, envp) == -1)
		ft_error_function();
}

void	ft_two_cmds(t_cmd *cmd, int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		n_cmd;
	t_cmd	*temp_cmd;
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe ");
		return ;
	}
	temp_cmd = cmd;
	n_cmd = 0;
	while (n_cmd <= 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (n_cmd == 0)
				ft_child(temp_cmd, argv[1], pipefd, envp);
			else
				ft_child(temp_cmd, argv[argc - 1], pipefd, envp);
		}
		n_cmd++;
		temp_cmd = temp_cmd->next;
	}
	if (pid > 0 && waitpid(-1, NULL, 0) == -1)
			perror("waitpid ");
	close(pipefd[0]);
	close(pipefd[1]);
}

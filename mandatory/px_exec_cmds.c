/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:13:57 by jduval            #+#    #+#             */
/*   Updated: 2023/02/21 09:05:29 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_cmd_not_found(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while(tmp != NULL)
	{
		if (tmp->flag == -1)
			ft_printf("command not found: %s\n", tmp->cmd[0]);
		tmp = tmp->next;
	}
	return ;
}

void	ft_close_fds(int fd1, int fd2, int fd3)
{
	if (fd1 > -1)
		close(fd1);
	if (fd2 > -1)
		close(fd2);
	if (fd3 > -1)
		close(fd3);
}

void	ft_child(t_cmd *cmd, char *argv, int *pipefd, char **envp)
{
	if (cmd->next == NULL)
	{
		ft_dup_last_cmd(pipefd, argv, cmd);
		if (cmd->flag == -1)
		{
			ft_free_all_cmd(&cmd);
			exit(0);
		}
		if (execve(cmd->cmd[0], cmd->cmd, envp) == -1)
			ft_error_function(cmd);
	}
	ft_dup_first_cmd(pipefd, argv, cmd);
	if (cmd->flag == -1)
	{
		printf("je passe\n");
		ft_free_all_cmd(&cmd);
		exit(0);
	}
	if (execve(cmd->cmd[0], cmd->cmd, envp) == -1)
	{
		printf("error child first cmd\n");
		ft_error_function(cmd);
	}
}

void	ft_two_cmds(t_cmd *cmd, int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		n_cmd;
	t_cmd	*temp_cmd;
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		printf("error pipe\n");
		ft_error_function(cmd);
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
	{
		printf("error waitpid\n");
		perror(NULL);
	}
	ft_close_fds(pipefd[0], pipefd[1], -1);
}

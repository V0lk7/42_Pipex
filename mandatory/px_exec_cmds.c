/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:13:57 by jduval            #+#    #+#             */
/*   Updated: 2023/02/23 13:39:29 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_close_fds(int fd1, int fd2, int fd3)
{
	if (fd1 > -1)
		close(fd1);
	if (fd2 > -1)
		close(fd2);
	if (fd3 > -1)
		close(fd3);
}

void	ft_error_cmd(char *str)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("' not found\n", 2);
}

static int	ft_last_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	if (i > 0)
		i--;
	return (i);
}

static int	ft_dispatch_cmd(t_cmd *cmd, char **argv, int *pipefd, char **envp)
{
	int	index;
	int	value;

	index = ft_last_arg(argv);
	if (cmd->position == 1)
		value = ft_first_cmd(cmd, argv[1], pipefd, envp);
	else
		value = ft_last_cmd(cmd, argv[index], pipefd, envp);
	if (value == 0)
		perror(NULL);
	return (value);
}

void	ft_loop_on_cmd(t_cmd *cmd, char **argv, char **envp)
{
	int		pipefd[2];
	int		wait_nbr;
	t_cmd	*tmp;

	wait_nbr = 0;
	if (pipe(pipefd) == -1)
	{
		perror("error pipe ");
		ft_free_lstcmd(&cmd);
		return ;
	}
	tmp = cmd;
	while (tmp != NULL)
	{
		wait_nbr += ft_dispatch_cmd(tmp, argv, pipefd, envp);
		tmp = ft_free_cmd(&tmp);
	}
	ft_close_fds(pipefd[0], pipefd[1], -1);
	while (wait_nbr > 0)
	{
		waitpid(-1, NULL, 0);
		wait_nbr--;
	}
}

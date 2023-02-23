/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_cmds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:42:11 by jduval            #+#    #+#             */
/*   Updated: 2023/02/23 16:39:24 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

static int	ft_dispatch_cmd(t_cmd *cmd, t_pipes *fd, char **argv, char **envp)
{
	int	index;
	int	value;

	index = ft_last_arg(argv);
	if (cmd->position == 1 && cmd->valid == 1)
			value = ft_here_doc(cmd, fd);
	else if(cmd->position == 1 && cmd->valid != 1)
		value = ft_first_multcmd(cmd, argv[1], fd, envp);
	else if (cmd->position > 1 && cmd->next != NULL && cmd->position % 2 == 0)
		value = ft_inter_even_cmd(cmd, fd, envp);
	else if (cmd->position > 1 && cmd->next != NULL && cmd->position % 2 != 0)
		value = ft_inter_odd_cmd(cmd, fd, envp);
	else if (cmd->next == NULL && cmd->position % 2 == 0)
		value = ft_last_even_cmd(cmd, argv[index], fd, envp);
	else
		value = ft_last_odd_cmd(cmd, argv[index], fd, envp);
	if (value == 0)
		perror(NULL);
	return (value);
}

static int	ft_open_pipes(t_pipes *fd)
{
	if (pipe(fd->pipe1) == -1)
		return (-1);
	if (pipe(fd->pipe2) == -1)
	{
		ft_close(fd);
		return (-1);
	}
	return (0);
}

void	ft_loop_on_cmd(t_cmd *cmd, char **argv, char **envp)
{
	t_pipes	*fd;
	int		wait_nbr;

	wait_nbr = 0;
	if (ft_open_pipes(fd) == -1)
	{
		ft_free_lstcmd(&cmd);
		perror(NULL);
		exit(0);
	}
	while (cmd != NULL)
	{
		wait_nbr += ft_dispatch_multpipe(cmd, fd, argv, envp);
		cmd = ft_free_cmd(&cmd);
	}
	ft_close(fd);
	while (wait_nbr > 0)
	{
		waitpid(-1, NULL, 0);
		wait_nbr--;
	}
}

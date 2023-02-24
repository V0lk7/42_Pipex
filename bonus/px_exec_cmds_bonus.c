/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_exec_cmds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:42:11 by jduval            #+#    #+#             */
/*   Updated: 2023/02/24 18:09:56 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static int	ft_mlt_pipe(t_cmd *cmd, t_pipes *fd, char **argv, char **envp)
{
	int	index;
	int	value;

	index = ft_last_arg(argv);
	//if (cmd->position == 1 && cmd->valid == 1)
	//		value = ft_here_doc(cmd, fd);
	if (cmd->position == 1 && cmd->valid != 1)
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

static int	ft_open_pipe(t_pipes *fd, int pair)
{
	if (pair == 1)
	{
		if (pipe(fd->pipe2) == -1)
			return (-1);
		return (0);
	}
	if (pipe(fd->pipe1) == -1)
		return (-1);
	return (0);
}

void	ft_close_pfd(t_pipes *fds, int fd)
{
	if (fds->pipe1[0] > -1)
		close(fds->pipe1[0]);
	if (fds->pipe1[1] > -1)
		close(fds->pipe1[1]);
	if (fds->pipe2[0] > -1)
		close(fds->pipe2[0]);
	if (fds->pipe2[1] > -1)
		close(fds->pipe2[1]);
	if (fd > -1)
		close(fd);
}

void	ft_loop_mlt_cmd(t_cmd *cmd, char **argv, char **envp)
{
	t_pipes	*fd;
	int		wait_nbr;

	wait_nbr = 0;
	fd = malloc(sizeof(t_pipes) * 1);
	while (cmd != NULL)
	{
		if (cmd->valid % 2 == 0)
		{
			if (ft_open_pipe(fd, 1) == -1)
			{
				ft_free_lstcmd(&cmd);
				ft_close_pfd(fd, -1);
				perror(NULL);
				exit(0);
			}
			wait_nbr += ft_mlt_pipe(cmd, fd, argv, envp);
			printf("%d\n%d\n", fd->pipe1[0], fd->pipe1[1]);
		}
		else
		{
			if (ft_open_pipe(fd, 0) == -1)
			{
				ft_free_lstcmd(&cmd);
				ft_close_pfd(fd, -1);
				perror(NULL);
				exit(0);
			}
			wait_nbr += ft_mlt_pipe(cmd, fd, argv, envp);
		}
		cmd = ft_free_cmd(&cmd);
	}
	while (wait_nbr > 0)
	{
		waitpid(-1, NULL, 0);
		wait_nbr--;
	}
}

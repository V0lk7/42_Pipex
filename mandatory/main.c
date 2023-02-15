/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:41:01 by jduval            #+#    #+#             */
/*   Updated: 2023/02/15 17:34:12 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_one_cmd(t_cmd *cmd, char *outfile, char **envp)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork ");
	if (pid == 0)
	{
		fd = open(outfile, O_TRUNC | O_RDWR, 777);
		if (fd == -1)
			ft_error_function();
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_error_function();
		if (close(fd) == -1)
			ft_error_function();
		if (execve(cmd->cmd[0], cmd->cmd, envp) == -1)
			ft_error_function();
	}
	if (pid > 0 && waitpid(-1, NULL, 0) == -1)
		perror(NULL);
	ft_free_node(&cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	//int		fd[2];
	int		nbr_cmds;

	cmd = ft_parsing(argc, argv, envp);
	nbr_cmds = ft_count_cmds(cmd);
	if (nbr_cmds == 1)
		ft_one_cmd(cmd, argv[argc - 1], envp);
	return (0);
}

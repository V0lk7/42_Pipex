/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:41:01 by jduval            #+#    #+#             */
/*   Updated: 2023/03/08 16:27:28 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	int		status;

	if (argc != 5)
	{
		ft_putstr_fd("Bad pathern !\nNeed 5 arguments\n", 2);
		return (0);
	}
	cmd = ft_parsing(argc, argv, envp);
	printf("valid = %d\n, cmd = %s\n", cmd->valid, cmd->cmd[0]);
	status = ft_exec_mandatory(cmd, argc, argv, envp);
	return (status);
}

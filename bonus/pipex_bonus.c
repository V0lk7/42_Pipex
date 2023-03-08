/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:41:01 by jduval            #+#    #+#             */
/*   Updated: 2023/03/08 10:57:49 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	int		hdoc;
	int		status;

	if (argc < 5)
	{
		ft_putstr_fd("Bad pathern !\nNeed at least, 5 arguments\n", 2);
		return (0);
	}
	cmd = ft_parsing(argc, argv, envp);
	hdoc = ft_build_hdoc(cmd, argv, argc);
	if (hdoc == -1)
	{
		ft_free_lstcmd(&cmd);
		return (0);
	}
	status = ft_loop_mlt_cmd(cmd, argc, argv, envp);
	return (status);
}

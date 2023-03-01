/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:41:01 by jduval            #+#    #+#             */
/*   Updated: 2023/03/01 12:44:26 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	int		hdoc;

	if (argc < 5)
	{
		ft_putstr_fd("Bad pathern !\nNeed at least, 5 arguments\n", 2);
		return (0);
	}
	cmd = ft_parsing(argc, argv, envp);
	hdoc = ft_build_hdoc(cmd, argv, argc);
	if (hdoc == -1 || hdoc == -2)
	{
		ft_free_lstcmd(&cmd);
		if (hdoc == -2)
			perror(NULL);
		return (0);
	}
	if (hdoc == 0 && argc == 5)
		ft_loop_on_cmd(cmd, argv, envp);
	else
		ft_loop_mlt_cmd(cmd, argc, argv, envp);
	return (0);
}

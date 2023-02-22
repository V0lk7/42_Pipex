/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:41:01 by jduval            #+#    #+#             */
/*   Updated: 2023/02/22 15:50:19 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;

	if (argc < 5)
	{
		ft_putstr_fd("Bad pathern !\nNeed at least, 5 arguments\n", 2);
		return (0);
	}
	cmd = ft_parsing(argc, argv, envp);
	ft_build_hdoc(&cmd);
	ft_loop_on_cmd(cmd, argv, envp);
	return (0);
}

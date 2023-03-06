/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:41:01 by jduval            #+#    #+#             */
/*   Updated: 2023/03/06 17:51:26 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static	void	ft_display(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	while (tmp != NULL)
	{
		i = 0;
		ft_printf("position = %d\n", tmp->position);
		ft_printf("valid = %d\n", tmp->valid);
		while (tmp->cmd[i] != NULL)
		{
			ft_printf("%s\n", tmp->cmd[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

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
	ft_display(cmd);
	if (hdoc == -1)
	{
		ft_free_lstcmd(&cmd);
		return (0);
	}
	status = ft_loop_mlt_cmd(cmd, argc, argv, envp);
	return (status);
}

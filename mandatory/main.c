/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:41:01 by jduval            #+#    #+#             */
/*   Updated: 2023/02/21 17:12:46 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_display(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i = 0;
	int		k = 0;

	tmp = cmd;
	while (tmp != NULL)
	{
		printf("|%i|\n", k);
		while (tmp->cmd[i])
		{
			printf("cmd[%i] = %s\n", i, tmp->cmd[i]);
			i++;
		}
		i = 0;
		k++;
		printf("flag = %i\n", cmd->flag);
		tmp = tmp->next;
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;

	cmd = ft_parsing(argc, argv, envp);
	ft_display(cmd);
	ft_cmd_not_found(cmd);
	ft_two_cmds(cmd, argc, argv, envp);
	ft_free_all_cmd(&cmd);
	return (0);
}

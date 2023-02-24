/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parse_hdoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:49:36 by jduval            #+#    #+#             */
/*   Updated: 2023/02/24 15:20:23 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	ft_build_hdoc(t_cmd *cmd, char **argv, int argc)
{
	if (strncmp(argv[1], "here_doc", 8) != 0)
		return (0);
	if (argc < 6)
		return (-1);
	if (cmd->valid == 0)
	{
		ft_free_array(cmd->cmd);
		cmd->cmd = malloc(sizeof(char *) * 2);
		if (cmd->cmd == NULL)
			return (-1);
		cmd->cmd[0] = ft_strdup(argv[2]);
		if (cmd->cmd[0] == NULL)
			return (-1);
		else
			cmd->cmd[1] = NULL;
		cmd->valid = 1;
	}
	else
		cmd->valid = 2;
	return (1);
}

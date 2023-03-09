/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parse_hdoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:49:36 by jduval            #+#    #+#             */
/*   Updated: 2023/03/09 09:59:43 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_fill_pipe(t_fds *fds, t_cmd *cmd)
{
	char	*input;
	int		fd;
	int		len;

	fd = STDIN_FILENO;
	len = ft_strlen(cmd->cmd[0]);
	input = ft_gnl(fd);
	while (input)
	{
		if (ft_strncmp(input, cmd->cmd[0], len) == 0
			&& ft_strlen(cmd->cmd[0]) == ft_strlen(input))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fds->write);
		free(input);
		input = ft_gnl(STDIN_FILENO);
	}
	if (input == NULL)
	{
		ft_free_lstcmd(&cmd);
		ft_close_fds(fds->write, fds->read, fd);
		exit(0);
	}
}

static void	ft_last_valid_hdoc(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	tmp = ft_last_node(tmp);
	if (tmp->valid == 0)
		tmp->valid = 1;
	else
		tmp->valid = 2;
}

static char	*ft_limiter(char *str)
{
	char	*limiter;
	int		len;

	len = ft_strlen(str);
	limiter = ft_calloc(len + 2, sizeof(char));
	if (limiter == NULL)
		return (NULL);
	ft_strlcpy(limiter, str, len + 1);
	limiter[len] = '\n';
	return (limiter);
}

int	ft_build_hdoc(t_cmd *cmd, char **argv, int argc)
{
	if (strncmp(argv[1], "here_doc", 8) == 0
		&& ft_strlen("here_doc") == ft_strlen(argv[1]))
	{
		if (argc < 6)
			return (-1);
		ft_free_array(cmd->cmd);
		cmd->cmd = malloc(sizeof(char *) * 2);
		if (cmd->cmd == NULL)
			return (-1);
		cmd->cmd[0] = ft_limiter(argv[2]);
		if (cmd->cmd[0] == NULL)
			return (-1);
		cmd->cmd[1] = NULL;
		cmd->valid = 1;
		ft_last_valid_hdoc(cmd);
		return (1);
	}
	return (0);
}

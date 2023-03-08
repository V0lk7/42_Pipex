/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:54:48 by jduval            #+#    #+#             */
/*   Updated: 2023/03/08 16:42:03 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**ft_wrong_cmd(char *str)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 2);
	if (cmd == NULL)
		return (NULL);
	cmd[0] = ft_strdup(str);
	if (cmd[0] == NULL)
		return (NULL);
	cmd[1] = NULL;
	return (cmd);
}

void	ft_error_cmd(char *str)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("' not found\n", 2);
}

t_cmd	*ft_parsing(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	**path;

	path = ft_envp_to_path(envp);
	cmd = ft_create_chain(argc, argv, path);
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

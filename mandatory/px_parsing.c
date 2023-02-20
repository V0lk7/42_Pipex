/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:54:48 by jduval            #+#    #+#             */
/*   Updated: 2023/02/20 15:47:21 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	*ft_parsing(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	**path;

	if (argc != 5)
	{
		ft_printf("ERROR\nPathern: ./pipex 'file1' 'cmd1' 'cmd2' 'file2'\n");
		exit (0);
	}
	path = ft_envp_to_path(envp);
	cmd = ft_create_chain(argc, argv, path);
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

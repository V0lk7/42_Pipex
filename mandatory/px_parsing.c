/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:54:48 by jduval            #+#    #+#             */
/*   Updated: 2023/02/07 16:11:55 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_files(int argc, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror(NULL);
}

t_cmd	ft_parsing(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	**paths;

	ft_open_files(argc, argv);
	paths = ft_envp_to_paths(envp);
}

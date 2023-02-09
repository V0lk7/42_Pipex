/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:54:48 by jduval            #+#    #+#             */
/*   Updated: 2023/02/09 14:56:15 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	ft_parsing(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	**path;
	t_file	file;

	file = ft_files(argc, argv);
	if (file == ERROR)
		exit(0);
	path = ft_envp_to_path(envp);
	cmd = ft_create_chain(argc, file, argv, path);
}

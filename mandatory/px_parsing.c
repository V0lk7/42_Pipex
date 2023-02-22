/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:54:48 by jduval            #+#    #+#             */
/*   Updated: 2023/02/22 14:24:46 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

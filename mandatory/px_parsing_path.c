/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:04:43 by jduval            #+#    #+#             */
/*   Updated: 2023/02/08 14:02:59 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_envp_to_path(char **envp)
{
	char	**path;
	int		index;
	
	index = ft_find_path(envp);
	if (index == -1)
	{
		ft_printf("PATH not found\n");
		exit (0);
	}
	path = ft_split(envp[index], ':');
	if (path == NULL)
		exit (0);
	return (path);
}

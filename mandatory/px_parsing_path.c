/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:04:43 by jduval            #+#    #+#             */
/*   Updated: 2023/02/09 18:20:39 by jduval           ###   ########.fr       */
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

char	*ft_remake_path(char *envp)
{
	char	*str;
	int		len;

	if (envp == NULL)
		return (NULL);
	len = ft_strlen(envp);
	str = ft_substr(envp, 5, len);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	**ft_envp_to_path(char **envp)
{
	char	**path;
	char	*str;
	int		index;
	
	index = ft_find_path(envp);
	if (index == -1)
	{
		ft_printf("PATH not found\n");
		exit (0);
	}
	str = ft_remake_path(envp[index]);
	if (str == NULL)
		exit (0);
	path = ft_split(str, ':');
	free(str);
	if (path == NULL)
		exit (0);
	return (path);
}

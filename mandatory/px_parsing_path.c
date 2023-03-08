/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:04:43 by jduval            #+#    #+#             */
/*   Updated: 2023/03/06 16:21:24 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_find_path(char **envp)
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

static char	*ft_remake_path(char *envp)
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

static char	**ft_build_envp(char *str)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(str, ':');
	if (path == NULL)
		return (NULL);
	while (path[i] != NULL)
	{
		path[i] = ft_strjoin_free(path[i], "/");
		if (path[i] == NULL)
			return (NULL);
		i++;
	}
	return (path);
}

static char	**ft_empty_path(void)
{
	char	**path;

	path = ft_calloc(sizeof(char *), 2);
	if (path == NULL)
		exit(0);
	return (path);
}

char	**ft_envp_to_path(char **envp)
{
	char	**path;
	char	*str;
	int		index;

	index = ft_find_path(envp);
	if (index == -1)
	{
		path = ft_empty_path();
		return (path);
	}
	str = ft_remake_path(envp[index]);
	if (str == NULL)
		exit (0);
	path = ft_build_envp(str);
	free(str);
	if (path == NULL)
		exit (0);
	return (path);
}

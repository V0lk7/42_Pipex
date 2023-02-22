/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:44:32 by jduval            #+#    #+#             */
/*   Updated: 2023/02/22 11:47:43 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_rebuild_cmd(char *str, char *cmd)
{
	char	*s;
	char	*new_s;

	s = ft_strchr(str, ' ');
	if (s == NULL)
		return (cmd);
	new_s = ft_strjoin_free(cmd, s);
	if (new_s == NULL)
		return (NULL);
	return (new_s);
}

char	*ft_only_cmd(char *str)
{
	int		i;
	int		len;
	char	*cmd;

	i = 0;
	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	cmd = ft_calloc(sizeof(char), len + 1);
	if (cmd == NULL)
		return (NULL);
	while (i < len)
	{
		cmd[i] = str[i];
		i++;
	}
	return (cmd);
}

char	**ft_check_all_path(char *str, char *cmd, char **path)
{
	int		i;
	int		value;
	char	**array;

	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin_free_s2(path[i], cmd);
		if (cmd == NULL)
			return (NULL);
		value = access(cmd, F_OK);
		if (value == 0)
			break ;
		free(cmd);
		cmd = ft_only_cmd(str);
	}
	cmd = ft_rebuild_cmd(str, cmd);
	if (cmd == NULL)
		return (NULL);
	array = ft_split(cmd, ' ');
	free(cmd);
	if (array == NULL)
		return (NULL);
	return (array);
}

char	**ft_check_cmd(char *str, char **path)
{
	int		value;
	char	*cmd;
	char	**array;

	cmd = ft_only_cmd(str);
	if (cmd == NULL)
		return (NULL);
	value = access(cmd, F_OK);
	if (value == 0)
	{
		cmd = ft_rebuild_cmd(str, cmd);
		if (cmd == NULL)
			return (NULL);
		array = ft_split(cmd, ' ');
		free(cmd);
		if (array == NULL)
			return (NULL);
		return (array);
	}
	array = ft_check_all_path(str, cmd, path);
	if (array == NULL)
		return (NULL);
	return (array);
}

char	**ft_make_cmd(char *str, char **path)
{
	char	**array;

	if (str[0] == '\0')
	{
		array = malloc(sizeof(char *) * 2);
		if (array == NULL)
			return (NULL);
		array[0] = ft_strdup(str);
		if (array[0] == NULL)
		{
			free(array);
			return (NULL);
		}
		array[1] = NULL;
		return (array);
	}
	else
		array = ft_check_cmd(str, path);
	return (array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:44:32 by jduval            #+#    #+#             */
/*   Updated: 2023/02/11 00:12:44 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_rebuild_cmd(char *str, char *cmd)
{
	char	*s;

	s = ft_strchr(str, ' ');
	if (s == NULL)
		return (cmd);
	cmd = ft_strjoin_free(cmd, s);
	if (cmd == NULL)
		return (NULL);
	return (cmd);
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
	char	**tab;

	i = 0;
	while (path[i] != NULL)
	{
		cmd = ft_strjoin_free_s2(path[i], cmd);
		if (cmd == NULL)
			return (NULL);
		value = access(cmd, F_OK);
		if (value == 0)
			break ;	
		free(cmd);
		cmd = ft_only_cmd(str);
		i++;
	}
	cmd = ft_rebuild_cmd(str, cmd);
	if (cmd == NULL)
		return (NULL);
	tab = ft_split(cmd, ' ');
	if (tab == NULL)
		return (NULL);
	return (tab);
}

char	**ft_check_cmd(char *str, char **path)
{
	int		value;
	char	*cmd;
	char	**tab;

	cmd = ft_only_cmd(str);
	if (cmd == NULL)
		return (NULL);
	value = access(cmd, F_OK);
	if (value == 0)
	{
		cmd = ft_rebuild_cmd(str, cmd);
		tab = ft_split(cmd, ' ');
		free(cmd);
		return (tab);
	}
	tab = ft_check_all_path(str, cmd, path);
	if (cmd != NULL)
		free(cmd);
	if (tab == NULL)
		return (NULL);
	return (tab);
}

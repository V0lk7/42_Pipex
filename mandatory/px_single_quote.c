/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_single_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:51:34 by jduval            #+#    #+#             */
/*   Updated: 2023/02/22 11:45:29 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_put_space(char *str)
{
	int		len;
	int		i;
	char	*new;

	len = ft_strlen(str);
	i = 0;
	new = ft_calloc(sizeof(char), len + 2);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, str, len + 1);
	new[len] = ' ';
	free(str);
	return (new);
}

char	*ft_rebuild_str(char **old_cmd)
{
	char	*reset;
	int		i;

	i = 0;
	reset = NULL;
	while (old_cmd[i])
	{
		old_cmd[i] = ft_put_space(old_cmd[i]);
		reset = ft_strjoin_free(reset, old_cmd[i]);
		if (reset == NULL)
			return (NULL);
		i++;
	}
	return (reset);
}

void	ft_put_flag(char **reset)
{
	int	i;

	i = 0;
	while ((*reset)[i])
	{
		if ((*reset)[i] && (*reset)[i] == 39)
		{
			i++;
			while ((*reset)[i] && (*reset)[i] != 39)
			{
				if ((*reset)[i] == ' ')
					(*reset)[i] = -128;
				i++;
			}
		}
		i++;
	}
}

char	**ft_build_cmd(char *reset)
{
	int		i;
	int		j;
	char	**cmd;

	ft_put_flag(&reset);
	cmd = ft_split(reset, ' ');
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (cmd[i] != NULL)
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == -128)
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (cmd);
}

char	**ft_single_quote(char *str, char **cmd)
{
	char	**new_cmd;
	char	*reset;
	int		quote;

	quote = ft_find_quotes(str);
	if (quote == 0 || quote % 2 != 0)
		return (cmd);
	reset = ft_rebuild_str(cmd);
	ft_free_array(cmd);
	if (reset == NULL)
		return (NULL);
	new_cmd = ft_build_cmd(reset);
	free(reset);
	if (new_cmd == NULL)
		return (NULL);
	return (new_cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_single_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:51:34 by jduval            #+#    #+#             */
/*   Updated: 2023/02/13 17:58:19 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_find_quotes(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == 39)
		 quote++;
		i++;
	}
	return (quote);
}

char	*ft_rebuild_str(char **old_cmd)
{
	char	*reset;
	int		i;

	i = 0;
	while (old_cmd[i])
	{
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
					(*reset)[i] = 127;
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
	ft_free_tab(cmd);
	if (reset == NULL)
		return (NULL);
	new_cmd = ft_build_cmd(reset);
	free(reset);
	if (new_cmd == NULL)
		return (NULL);
	return (new_cmd);
}

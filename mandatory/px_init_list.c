/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_init_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:58:12 by jduval            #+#    #+#             */
/*   Updated: 2023/02/10 16:30:04 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	*ft_create_node(char *str, char **path)
{
	t_cmd	*node;
	char	**cmd_line;

	cmd_line = ft_check_cmd(str, path);
	if (cmd_line == NULL)
		return (NULL);
	node = ft_new_node(cmd_line);
	if (node == NULL)
		return (NULL);
	return (node);
}
/*
t_cmd	*ft_create_chain(int argc, t_file file, char **argv, char **path)
{
	int		i;
	t_cmd	*node;
	t_cmd	*tmp;

	i = 2;
	if (file == NO_INFILE)
		i = 3;
	while (i < argc)
	{
		tmp = ft_create_node(argv[i], path);
		i++;
	}
}*/

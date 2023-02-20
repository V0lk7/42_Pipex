/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_init_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:58:12 by jduval            #+#    #+#             */
/*   Updated: 2023/02/20 16:50:03 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	*ft_create_node(char *str, char **path)
{
	t_cmd	*node;
	char	**cmd_line;
	int		flag;

	cmd_line = ft_check_cmd(str, path);
	cmd_line = ft_single_quote(str, cmd_line);
	if (cmd_line == NULL)
		return (NULL);
	flag = access(str, F_OK);
	node = ft_new_node(cmd_line, flag);
	if (node == NULL)
		return (NULL);
	return (node);
}

t_cmd	*ft_create_chain(int argc, char **argv, char **path)
{
	int		i;
	t_cmd	*head;
	t_cmd	*node;

	i = 2;
	head = ft_create_node(argv[i], path);
	if (head == NULL)
		return (NULL);
	i++;
	while (i < argc - 1)
	{
		node = ft_create_node(argv[i], path);
		if (node == NULL)
		{
			ft_free_all_cmd(&head);
			ft_free_tab(path);
			return (NULL);
		}
		ft_add_back_node(&head, node);
		i++;
	}
	ft_free_tab(path);
	return (head);
}

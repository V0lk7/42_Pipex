/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_init_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:58:12 by jduval            #+#    #+#             */
/*   Updated: 2023/02/21 09:10:06 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_cmd	*ft_create_node(char *str, char **path)
{
	t_cmd	*node;
	char	**cmd_line;
	int		flag;

	cmd_line = ft_check_cmd(str, path);
	cmd_line = ft_single_quote(str, cmd_line);
	if (cmd_line == NULL)
		return (NULL);
	flag = access(cmd_line[0], F_OK);
	node = ft_new_node(cmd_line, flag);
	if (node == NULL)
	{
		ft_free_array(cmd_line);
		return (NULL);
	}
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

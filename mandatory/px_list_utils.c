/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:37:20 by jduval            #+#    #+#             */
/*   Updated: 2023/02/22 09:41:17 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	*ft_new_node(char **array, int valid, int position)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->cmd = array;
	new->valid = valid;
	new->position = position;
	new->next = NULL;
	return (new);
}

void	ft_add_back_node(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (head == NULL || new == NULL)
		return ;
	if ((*head) == NULL)
		*head = new;
	else
	{
		tmp = ft_last_node(*head);
		tmp->next = new;
	}
	return ;
}

t_cmd	*ft_last_node(t_cmd *head)
{
	t_cmd	*tmp;

	if (head == NULL)
		return (NULL);
	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

int	ft_count_cmds(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

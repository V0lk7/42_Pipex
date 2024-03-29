/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:23:49 by jduval            #+#    #+#             */
/*   Updated: 2023/02/22 08:29:18 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_lstcmd(t_cmd **head)
{
	t_cmd	*tmp;

	while ((*head) != NULL)
	{
		tmp = (*head);
		(*head) = (*head)->next;
		ft_free_array(tmp->cmd);
		free(tmp);
	}
}

t_cmd	*ft_free_cmd(t_cmd **head)
{
	t_cmd	*tmp;

	tmp = (*head);
	(*head) = (*head)->next;
	if (tmp->cmd != NULL)
		ft_free_array(tmp->cmd);
	free(tmp);
	return ((*head));
}

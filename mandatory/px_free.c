/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:23:49 by jduval            #+#    #+#             */
/*   Updated: 2023/02/15 17:12:20 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_all_cmd(t_cmd **head)
{
	t_cmd	*tmp;

	while ((*head) != NULL)
	{
		tmp = (*head);
		(*head) = (*head)->next;
		ft_free_tab(tmp->cmd);
		free(tmp);
	}
}

t_cmd	*ft_free_node(t_cmd **head)
{
	t_cmd	*tmp;

	tmp = (*head);
	(*head) = (*head)->next;
	if (tmp->cmd != NULL)
		ft_free_tab(tmp->cmd);
	free(tmp);
	return ((*head));
}

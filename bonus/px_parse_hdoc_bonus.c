/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parse_hdoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:49:36 by jduval            #+#    #+#             */
/*   Updated: 2023/02/23 13:47:35 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_build_hdoc(t_cmd **cmd, char **argv, int argc)
{
	if (strncmp(argv[1], "here_doc", 8) != 0)
		return (0);
	if (argc < 6)
		return (-1);
	if ((*cmd)->valid == 0)
	{
		ft_free_array((*cmd)->array);
		(*cmd)->array = malloc(sizeof(char *) * 2);
		if ((*cmd)->array == NULL)
			return (-1);
		(*cmd)->array[0] = ft_strdup(argv[2])
		if ((*cmd)->array[0] == NULL)
			return (-1);
		(*cmd)->array[1] = NULL;
		(*cmd)->valid = 1;
	}
	return (1);
}

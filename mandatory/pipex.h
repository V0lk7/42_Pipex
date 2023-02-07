/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:15:13 by jduval            #+#    #+#             */
/*   Updated: 2023/02/07 13:55:11 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>

typedef struct s_cmd
{
	char **cmd;
	struct s_command	*next;
}	t_cmd;

//			px_parsing			//
t_cmd	ft_parse(int argc, char **argv, char **envp);

#endif

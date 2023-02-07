/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:15:13 by jduval            #+#    #+#             */
/*   Updated: 2023/02/07 17:05:33 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <stdio.h>

typedef struct s_cmd
{
	char **cmd;
	struct s_command	*next;
}	t_cmd;

//			px_parsing			//
//t_cmd	ft_parse(int argc, char **argv, char **envp);
//			px_parsing_files			//
t_bool	ft_infile(char **argv);
t_bool	ft_outfile(int argc, char **argv);
void	ft_files(int argc, char **argv);

#endif

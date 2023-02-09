/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:15:13 by jduval            #+#    #+#             */
/*   Updated: 2023/02/09 17:54:26 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_cmd
{
	char 			**cmd;
	int				error;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_file
{
	ERROR,
	NO_INFILE,
	INFILE
}	t_file;

//////////////////////////////////////////////////////////////////////////////
//								px_parsing.c								//
//////////////////////////////////////////////////////////////////////////////
t_cmd	ft_parse(int argc, char **argv, char **envp);
//////////////////////////////////////////////////////////////////////////////
//								px_parsing_files							//
//////////////////////////////////////////////////////////////////////////////
t_file	ft_infile(char **argv);
t_bool	ft_outfile(int argc, char **argv);
t_file	ft_files(int argc, char **argv);
//////////////////////////////////////////////////////////////////////////////
//								px_parsing_path								//
//////////////////////////////////////////////////////////////////////////////
int		ft_find_path(char **envp);
char	*ft_remake_path(char *envp);
char	**ft_envp_to_path(char **envp);
//////////////////////////////////////////////////////////////////////////////
//								px_free.c									//
//////////////////////////////////////////////////////////////////////////////
void	ft_free_tab(char **tab);
void	ft_free_all_cmd(t_cmd *head);
void	ft_free_node(t_cmd *head);
//////////////////////////////////////////////////////////////////////////////
//								px_list_utils.c								//
//////////////////////////////////////////////////////////////////////////////
t_cmd	*ft_new_node(char **tab, int flag);
void	ft_add_back_node(t_cmd **head, t_cmd *new);
t_cmd	*ft_last_node(t_cmd *head);
//////////////////////////////////////////////////////////////////////////////

#endif

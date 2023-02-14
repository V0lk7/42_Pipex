/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:15:13 by jduval            #+#    #+#             */
/*   Updated: 2023/02/14 13:09:20 by jduval           ###   ########.fr       */
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
	char			**cmd;
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
char	**ft_build_envp(char *str);
char	**ft_envp_to_path(char **envp);
//////////////////////////////////////////////////////////////////////////////
//								px_free.c									//
//////////////////////////////////////////////////////////////////////////////
void	ft_free_tab(char **tab);
void	ft_free_all_cmd(t_cmd **head);
void	ft_free_node(t_cmd *head);
//////////////////////////////////////////////////////////////////////////////
//								px_list_utils.c								//
//////////////////////////////////////////////////////////////////////////////
t_cmd	*ft_new_node(char **tab);
void	ft_add_back_node(t_cmd **head, t_cmd *new);
t_cmd	*ft_last_node(t_cmd *head);
//////////////////////////////////////////////////////////////////////////////
//								px_parse_cmd.c								//
//////////////////////////////////////////////////////////////////////////////
char	*ft_rebuild_cmd(char *str, char *cmd);
char	*ft_only_cmd(char *str);
char	**ft_check_all_path(char *str, char *cmd, char **path);
char	**ft_check_cmd(char *str, char **path);
//////////////////////////////////////////////////////////////////////////////
//								px_init_list.c								//
//////////////////////////////////////////////////////////////////////////////
t_cmd	*ft_create_node(char *str, char **path);
t_cmd	*ft_create_chain(int argc, t_file file, char **argv, char **path);
//////////////////////////////////////////////////////////////////////////////
//								px_single_quote.c							//
//////////////////////////////////////////////////////////////////////////////
int		ft_find_quotes(char *str);
char	*ft_put_space(char *str);
char	*ft_rebuild_str(char **old_cmd);
void	ft_put_flag(char **reset);
char	**ft_build_cmd(char *reset);
char	**ft_single_quote(char *str, char **cmd);
//////////////////////////////////////////////////////////////////////////////
//								px_parsing.c								//
//////////////////////////////////////////////////////////////////////////////
char	*ft_strjoin_free_s2(char *s1, char *s2);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:15:13 by jduval            #+#    #+#             */
/*   Updated: 2023/02/22 13:02:15 by jduval           ###   ########.fr       */
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
	int				valid;
	int				position;
	struct s_cmd	*next;
}	t_cmd;

//////////////////////////////////////////////////////////////////////////////
//								px_parsing.c								//
//////////////////////////////////////////////////////////////////////////////
t_cmd	*ft_parsing(int argc, char **argv, char **envp);
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
void	ft_free_array(char **array);
void	ft_free_lstcmd(t_cmd **head);
t_cmd	*ft_free_cmd(t_cmd **head);
//////////////////////////////////////////////////////////////////////////////
//								px_list_utils.c								//
//////////////////////////////////////////////////////////////////////////////
t_cmd	*ft_new_node(char **array, int valid, int position);
void	ft_add_back_node(t_cmd **head, t_cmd *new);
t_cmd	*ft_last_node(t_cmd *head);
int		ft_count_node(t_cmd *head);
//////////////////////////////////////////////////////////////////////////////
//								px_parse_cmd.c								//
//////////////////////////////////////////////////////////////////////////////
char	*ft_rebuild_cmd(char *str, char *cmd);
char	*ft_only_cmd(char *str);
char	**ft_check_all_path(char *str, char *cmd, char **path);
char	**ft_check_cmd(char *str, char **path);
char	**ft_make_cmd(char *str, char **path);
//////////////////////////////////////////////////////////////////////////////
//								px_init_list.c								//
//////////////////////////////////////////////////////////////////////////////
t_cmd	*ft_create_node(char *str, char **path, int position);
t_cmd	*ft_create_chain(int argc, char **argv, char **path);
//////////////////////////////////////////////////////////////////////////////
//								px_single_quote.c							//
//////////////////////////////////////////////////////////////////////////////
char	*ft_put_space(char *str);
char	*ft_rebuild_str(char **old_cmd);
void	ft_put_flag(char **reset);
char	**ft_build_cmd(char *reset);
char	**ft_single_quote(char *str, char **cmd);
//////////////////////////////////////////////////////////////////////////////
//								px_utils.c									//
//////////////////////////////////////////////////////////////////////////////
char	*ft_strjoin_free_s2(char *s1, char *s2);
int		ft_find_quotes(char *str);
//////////////////////////////////////////////////////////////////////////////
//								px_exec_cmds.c								//
//////////////////////////////////////////////////////////////////////////////
void	ft_close_fds(int fd1, int fd2, int fd3);
void	ft_error_cmd(char *str);
void	ft_dispatch(t_cmd *cmd, char **argv, int *pipefd, char **envp);
void	ft_loop_on_cmd(t_cmd *cmd, char **argv, char **envp);
//////////////////////////////////////////////////////////////////////////////
//								px_first_exec.c								//
//////////////////////////////////////////////////////////////////////////////
int		ft_first_cmd(t_cmd *cmd, char *file, int *pipefd, char **envp);
//////////////////////////////////////////////////////////////////////////////
//								px_last_exec.c								//
//////////////////////////////////////////////////////////////////////////////
int		ft_last_cmd(t_cmd *cmd, char *file, int *pipefd, char **envp);
#endif

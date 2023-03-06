/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:34:57 by jduval            #+#    #+#             */
/*   Updated: 2023/03/06 18:46:44 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

//////////////////////////////////////////////////////////////////////////////
//								px_parse_hdoc_bonus.c						//
//////////////////////////////////////////////////////////////////////////////
void	ft_fill_pipe(t_fds *fd, t_cmd *cmd, char *hdoc);
int		ft_build_hdoc(t_cmd *cmd, char **argv, int argc);
//////////////////////////////////////////////////////////////////////////////
//								px_exec_cmds_bonus							//
//////////////////////////////////////////////////////////////////////////////
int		ft_loop_mlt_cmd(t_cmd *cmd, int argc, char **argv, char **envp);
int		ft_open_infile(char *file, t_cmd *cmd);
void	ft_open_fd(t_cmd *cmd, t_fds *fd, char *str);
void	ft_child(t_fds *fd, t_cmd *cmd, char **envp, char *hdoc);
void	ft_dup_fds(t_fds *fd, t_cmd *cmd, char *hdoc);
#endif
